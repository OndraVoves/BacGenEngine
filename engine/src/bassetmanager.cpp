/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2011  <copyright holder> <email>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include "../include/bassetmanager.h"

#include "../include/babstractasset.h"
#include "../include/babstractmodulesystem.h"
#include "../include/bproject.h"
#include "../include/blogger.h"

namespace BackGenEngine {

    BAssetManager::BAssetManager ( BProject *pc_project, BLogger *logger ) : pcProject ( pc_project ), Logger ( logger ) {
        BGE_LOGGER_DEBUG ( Logger, "BAssetManager", "BAssetManager", "" );
    }

    BAssetManager::~BAssetManager() {
        BGE_LOGGER_DEBUG ( Logger, "BAssetManager", "~BAssetManager", "" );

        asset_hash_t::ConstIterator it = AssetHash.constBegin();
        while ( it != AssetHash.constEnd() ) {
            delete ( *it );
            ++it;
        }
    }

    BAssetManager::asset_hash_t::ConstIterator BAssetManager::constBegin() const {
        return AssetHash.constBegin();
    }

    BAssetManager::asset_hash_t::ConstIterator BAssetManager::constEnd() const {
        return AssetHash.constEnd();
    }

    bool BAssetManager::containAsset ( const BoxE::Core::BAsciiString &name ) const {
        AssetHash.contains ( name );
    }

    BAbstractAsset *BAssetManager::getAsset ( const BoxE::Core::BAsciiString &name ) {
        asset_hash_t::Iterator it = AssetHash.find ( name );
        if ( it != AssetHash.end() ) {
            return ( *it );
        } else {
            return 0;
        }
    }

    bool BAssetManager::insertAsset ( BAbstractAsset *asset ) {
        if ( asset == 0 ) {
            return false;
        }

        BGE_LOGGER_DEBUG ( Logger, "BAssetManager", "insertAsset", BoxE::Core::BAsciiString ( "Inserting asset \"%1\"" ).replace ( "%1", asset->getName() ) );

        if ( AssetHash.insert ( asset->getName(), asset ) ) {
            asset->onNameChanged().connect ( this, &BAssetManager::onAssetNameChaned );
            return true;
        } else {
            return false;
        }

    }

    bool BAssetManager::removeAsset ( BAbstractAsset *asset ) {
        if ( asset == 0 ) {
            return false;
        }

        BGE_LOGGER_DEBUG ( Logger, "BAssetManager", "removeAsset", BoxE::Core::BAsciiString ( "Removing asset \"%1\"" ).replace ( "%1", asset->getName() ) );

        asset_hash_t::Iterator it = AssetHash.find ( asset->getName() );
        if ( it != AssetHash.end() ) {
            AssetHash.erase ( it );
            ( *it )->onNameChanged().disconnect ( this, &BAssetManager::onAssetNameChaned );
            return true;

        } else {
            return false;
        }
    }

    BoxE::Core::BByteArray BAssetManager::toByteArray() {
        BoxE::Core::BAsciiString str ( "assets_manager {\n"
                                       "%1"
                                       "}\n" );

        BoxE::Core::BAsciiString assets_str;
        BoxE::Core::BAsciiString asset_str;
        asset_hash_t::ConstIterator it = AssetHash.constBegin();
        while ( it != AssetHash.constEnd() ) {
            asset_str = "\tasset %1 %2 %3\n";
            asset_str.replace ( "%1", ( *it )->getName() );
            asset_str.replace ( "%2", ( *it )->getAssetType() );
            asset_str.replace ( "%3", ( *it )->getPath() );

            assets_str.append ( asset_str );
            ++it;
        }

        str.replace ( "%1", assets_str );

        return str;
    }

    bool BAssetManager::fromByteArray ( const BoxE::Core::BByteArray &byte_array, BackGenEngine::BAbstractRenderer *pc_renderer ) {
        BoxE::Core::BByteArray array ( byte_array );

        array.replace ( "\n", BoxE::Core::BByteArray ( " " ) );
        array.replace ( "\t", BoxE::Core::BByteArray ( "" ) );

        BoxE::Core::BLinkedList< BoxE::Core::BByteArray > list = array.split ( ' ' );

        BoxE::Core::BLinkedList< BoxE::Core::BByteArray >::Iterator rem_it = list.begin();
        // remove empty
        while ( rem_it != list.end() ) {
            if ( ( *rem_it ).isEmpty() )  {
                rem_it = list.erase ( rem_it );
                continue;
            }
            ++rem_it;
        }

        // parse command
        BoxE::Core::BLinkedList< BoxE::Core::BByteArray >::ConstIterator it = list.constBegin();
        int block_count = -1;
        while ( it != list.constEnd() ) {
            if ( ( *it ) == "assets_manager" ) {
                ++it;
                if ( ( *it ) == "{" ) {
                    while ( it != list.constEnd() ) {
                        ++it;
                        if ( ( *it ) == "}" ) {
                            return true;
                        } else if ( ( *it ) == "asset" ) {
                            // Name
                            if ( ( ++it ) == list.constEnd() ) {
                                return false;
                            }
                            BoxE::Core::BAsciiString name ( ( *it ) );

                            // type
                            if ( ( ++it ) == list.constEnd() ) {
                                return false;
                            }
                            BoxE::Core::BAsciiString type ( ( *it ) );

                            // path
                            if ( ( ++it ) == list.constEnd() ) {
                                return false;
                            }
                            BoxE::Core::BAsciiString path ( ( *it ) );

                            BAbstractAsset *pc_asset = pcProject->getModuleSystem()->createAsset ( type, pcProject, pc_renderer, this, Logger );
                            if ( pc_asset ) {
                                pc_asset->setName ( name );
                                pc_asset->setPath ( path );
                            } else {
                                continue;
                            }

                            insertAsset ( pc_asset );
                            continue;
                        }
                    }
                } else {
                    return false;
                }
            }
            ++it;
        }
    }

    void BAssetManager::onAssetNameChaned ( BAbstractAsset *asset, BoxE::Core::BAsciiString new_name  ) {
        asset_hash_t::Iterator it = AssetHash.find ( asset->getName() );

        if ( it != AssetHash.end() ) {
            AssetHash.erase ( it );
            AssetHash.insert ( new_name, asset );
        }
    }

}