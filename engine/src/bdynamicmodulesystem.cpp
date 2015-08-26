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


#include "../include/bdynamicmodulesystem.h"
#include "../include/bcomponentmodule.h"
#include "../include/bassetmodule.h"
#include "../include/bassetloadermodule.h"
#include "../include/bassetsavermodule.h"
#include "../include/blogger.h"

#include <BoxE/BFile>

namespace BackGenEngine {

    typedef void ( get_base_header_t ) ( BBaseModuleHeader_t * );
    typedef void ( get_asset_loader_header_t ) ( BAssetLoaderModuleHeader_t * );
    typedef void ( get_asset_saver_header_t ) ( BAssetSaverModuleHeader_t * );

    BDynamicModuleSystem::BDynamicModuleSystem ( BLogger *logger ) : BAbstractModuleSystem ( logger ) {
    }

    BDynamicModuleSystem::~BDynamicModuleSystem() {
        unloadAllComponent();
        unloadAllAsset();
    }

    BAbstractComponent *BDynamicModuleSystem::createComponent ( const BoxE::Core::BAsciiString &name, BScene *pc_scene ) {
        component_module_hash_t::Iterator it = ComponentModuleHash.find ( name );
        if ( it != ComponentModuleHash.end() ) {
            return ( *it )->create ( pc_scene );
        } else {
            return 0;
        }
    }

    BAbstractAsset *BDynamicModuleSystem::createAsset ( const BoxE::Core::BAsciiString &name,  BProject *pc_project, BackGenEngine::BAbstractRenderer *pc_renderer,  BAssetManager *pc_asset_manager, BLogger *pc_logger  ) {
        asset_module_hash_t::Iterator it = AssetModuleHash.find ( name );
        if ( it != AssetModuleHash.end() ) {
            return ( *it )->create ( pc_project, pc_renderer, pc_logger, this, pc_asset_manager );
        } else {
            return 0;
        }
    }

    bool BDynamicModuleSystem::loadAsset ( const BoxE::Core::BAsciiString &name, BAbstractAsset *asset, BoxE::Core::BIODevice *data, BAssetManager *pc_asset_manager, BLogger *pc_logger ) {
        if ( asset == 0 ) {
            return false;
        }

        asset_loader_module_hash_t::Iterator it = AssetLoaderModuleHash.find ( name );
        if ( it != AssetLoaderModuleHash.end() ) {
            return ( *it )->load ( asset, data,  pc_asset_manager, pc_logger );
        } else {
            return false;
        }
    }

    bool BDynamicModuleSystem::saveAsset ( const BoxE::Core::BAsciiString &name, BAbstractAsset *asset, BoxE::Core::BIODevice *data, BLogger *pc_logger ) {
        if ( asset == 0 ) {
            return false;
        }

        asset_saver_module_hash_t::Iterator it = AssetSaverModuleHash.find ( name );
        if ( it != AssetSaverModuleHash.end() ) {
            return ( *it )->save ( asset , data, pc_logger );
        } else {
            return false;
        }
    }

    bool BDynamicModuleSystem::loadModule ( const BoxE::Core::BAsciiString &path ) {
        if ( path.isEmpty() ) {
            return false;
        }

        Logger->info ( BoxE::Core::BAsciiString ( "Loading module from: %1" ).replace ( "%1", path ) );

        BoxE::Core::BLibrary *lib = 0;

        // TODO: zmenit z boxe na interni,,
        BOXE_TRY {
            lib = new BoxE::Core::BLibrary ( path );

            B_CHECK_PTR ( lib );

        } BOXE_CATCH ( const std::bad_alloc & ) {
            BOXE_RETHROW;
        }

        if ( lib->load() ) {
            get_base_header_t *getBaseHeader = ( get_base_header_t * ) lib->resolv ( "getBaseHeader" );

            if ( getBaseHeader == 0 ) {
                Logger->error ( "Could not read module header." );
                delete lib;
                return false;
            }

            BBaseModuleHeader_t base_header;
            getBaseHeader ( &base_header );

            if ( !parseBaseHeader ( &base_header ) ) {
                Logger->error ( "Invalid module header." );
                delete lib;
                return false;
            }

            Logger->debug ( BoxE::Core::BAsciiString ( "Actual module info:\n\tName: %1\n\tPath: %2\n\tType: %3\n\tVersion: %4\n\tAuthor: %5\n" )
                            .replace ( "%1", BoxE::Core::BAsciiString ( base_header.Name ) )
                            .replace ( "%2", lib->filename() )
                            .replace ( "%3", EModulesType2String ( base_header.Type ) )
                            .replace ( "%4", BoxE::Core::BAsciiString ( base_header.Version ) )
                            .replace ( "%5", BoxE::Core::BAsciiString ( base_header.Author ) ) );

            switch ( base_header.Type ) {
                case COMPONENT:
                    if ( !insertComponentModule ( lib, &base_header ) ) {
                        Logger->error ( "Could not insert component module." );
                        return false;
                    }
                    return true;

                case ASSET:
                    if ( !insertAssetModule ( lib, &base_header ) ) {
                        Logger->error ( "Could not insert asset module." );
                        return false;
                    }
                    return true;


                case ASSET_LOADER: {
                    // TODO: this code must go to other fce...
                    get_asset_loader_header_t *getAssetLoaderHeader = ( get_asset_loader_header_t * ) lib->resolv ( "getAssetLoaderModuleHeader" );

                    if ( getAssetLoaderHeader == 0 ) {
                        Logger->error ( "Could not read asset loader module header." );
                        delete lib;
                        return false;
                    }

                    BAssetLoaderModuleHeader_t asset_header;
                    getAssetLoaderHeader ( &asset_header );

                    if ( !parseAssetLoaderHeader ( &asset_header ) ) {
                        Logger->error ( "Invalid asset loader module header." );
                        delete lib;
                        return false;
                    }

                    if ( !insertAssetLoaderModule ( lib, &base_header, &asset_header ) ) {
                        Logger->error ( "Could not insert asset loader module." );
                        return false;
                    }
                    return true;
                }

                case ASSET_SAVER: {
                    // TODO: this code must go to other fce...
                    get_asset_saver_header_t *getAssetSaverHeader = ( get_asset_saver_header_t * ) lib->resolv ( "getAssetSaverModuleHeader" );

                    if ( getAssetSaverHeader == 0 ) {
                        Logger->error ( "Could not read asset saver module header." );
                        delete lib;
                        return false;
                    }

                    BAssetSaverModuleHeader_t asset_header;
                    getAssetSaverHeader ( &asset_header );

                    if ( !parseAssetSaverHeader ( &asset_header ) ) {
                        Logger->error ( "Invalid asset saver module header." );
                        delete lib;
                        return false;
                    }

                    if ( !insertAssetSaverModule ( lib, &base_header, &asset_header ) ) {
                        Logger->error ( "Could not insert asset saver module." );
                        return false;
                    }
                    return true;
                }

                case MODULES_TYPE_LAST_ITEM:
                default:
                    return false;
            }

        } else {
            Logger->error (  BoxE::Core::BAsciiString ( "Could not open module file. " ) << lib->errorString() );
            delete lib;
            return false;
        }
    }

    bool BDynamicModuleSystem::unloadModule ( const BoxE::Core::BAsciiString &name ) {
        component_module_hash_t::Iterator it = ComponentModuleHash.find ( name );
        if ( it != ComponentModuleHash.end() ) {
            delete ( *it );
            ComponentModuleHash.erase ( it );
        } else {
            return false;
        }
    }

    BDynamicModuleSystem::component_module_hash_t::ConstIterator BDynamicModuleSystem::constComponentBegin() const {
        return ComponentModuleHash.constBegin();
    }

    BDynamicModuleSystem::component_module_hash_t::ConstIterator BDynamicModuleSystem::constComponentEnd() const {
        return ComponentModuleHash.constEnd();
    }

    const BDynamicModuleSystem::asset_module_hash_t &BDynamicModuleSystem::getAssetModuleHash() const {
        return AssetModuleHash;
    }

    const BDynamicModuleSystem::asset_loader_module_hash_t &BDynamicModuleSystem::getAssetLoaderHash() const {
        return AssetLoaderModuleHash;
    }

    bool BDynamicModuleSystem::parseBaseHeader ( BBaseModuleHeader_t *header ) {
        if ( header == 0 ) {
            return false;
        }

        if ( header->Type >= MODULES_TYPE_LAST_ITEM ) {
            return false;
        }

        return true;
    }

    bool BDynamicModuleSystem::parseAssetLoaderHeader ( BAssetLoaderModuleHeader_t *header ) {
        if ( header == 0 ) {
            return false;
        } else {
            return true;
        }
    }

    bool BDynamicModuleSystem::parseAssetSaverHeader ( BAssetSaverModuleHeader_t *header ) {
        if ( header == 0 ) {
            return false;
        } else {
            return true;
        }
    }

    bool BDynamicModuleSystem::insertComponentModule ( BoxE::Core::BLibrary *lib, BBaseModuleHeader_t *header ) {
        if ( ComponentModuleHash.contains ( header->Name ) ) {
            return false;
        }

        BComponentModule *component_module  = 0;
        // TODO: zmenit z boxe na interni,,
        BOXE_TRY {
            component_module = new BComponentModule ( lib );

            B_CHECK_PTR ( component_module );

        } BOXE_CATCH ( const std::bad_alloc & ) {
            BOXE_RETHROW;
        }


        if ( !component_module->load() ) {
            delete component_module;
            return false;
        }

        if ( ComponentModuleHash.insert ( header->Name, component_module ) ) {
            return true;
        } else {
            delete component_module;
            return false;
        }
    }

    void BDynamicModuleSystem::unloadAllComponent() {
        component_module_hash_t::Iterator it = ComponentModuleHash.begin();
        while ( it != ComponentModuleHash.end() ) {
            delete ( *it );
            it = ComponentModuleHash.erase ( it );
        }
    }

    bool BDynamicModuleSystem::insertAssetModule ( BoxE::Core::BLibrary *lib, BBaseModuleHeader_t *header ) {
        if ( AssetModuleHash.contains ( header->Name ) ) {
            return false;
        }

        BAssetModule *asset_module  = 0;
        // TODO: zmenit z boxe na interni,,
        BOXE_TRY {
            asset_module = new BAssetModule ( lib );

            B_CHECK_PTR ( asset_module );

        } BOXE_CATCH ( const std::bad_alloc & ) {
            BOXE_RETHROW;
        }


        if ( !asset_module->load() ) {
            delete asset_module;
            return false;
        }

        if ( AssetModuleHash.insert ( header->Name, asset_module ) ) {
            return true;
        } else {
            delete asset_module;
            return false;
        }
    }

    void BDynamicModuleSystem::unloadAllAsset() {
        asset_module_hash_t::Iterator it = AssetModuleHash.begin();
        while ( it != AssetModuleHash.end() ) {
            delete ( *it );
            it = AssetModuleHash.erase ( it ); // this is not good idea...
        }
    }

    bool BDynamicModuleSystem::insertAssetLoaderModule ( BoxE::Core::BLibrary *lib, BBaseModuleHeader_t *base_header, BAssetLoaderModuleHeader_t *header ) {
        if ( AssetLoaderModuleHash.contains ( base_header->Name ) ) {
            return false;
        }

        BAssetLoaderModule *loader_module  = 0;
        // TODO: zmenit z boxe na interni,,
        BOXE_TRY {
            loader_module = new BAssetLoaderModule ( lib, header->AssetName );

            B_CHECK_PTR ( loader_module );

        } BOXE_CATCH ( const std::bad_alloc & ) {
            BOXE_RETHROW;
        }


        if ( !loader_module->load() ) {
            delete loader_module;
            return false;
        }

        if ( AssetLoaderModuleHash.insert ( base_header->Name, loader_module ) ) {
            return true;
        } else {
            delete loader_module;
            return false;
        }
    }

    bool BDynamicModuleSystem::insertAssetSaverModule ( BoxE::Core::BLibrary *lib, BBaseModuleHeader_t *base_header, BAssetSaverModuleHeader_t *header ) {
        if ( AssetSaverModuleHash.contains ( base_header->Name ) ) {
            return false;
        }

        BAssetSaverModule *saver_module  = 0;
        // TODO: zmenit z boxe na interni,,
        BOXE_TRY {
            saver_module = new BAssetSaverModule ( lib );

            B_CHECK_PTR ( saver_module );

        } BOXE_CATCH ( const std::bad_alloc & ) {
            BOXE_RETHROW;
        }


        if ( !saver_module->load() ) {
            delete saver_module;
            return false;
        }

        if ( AssetSaverModuleHash.insert ( base_header->Name, saver_module ) ) {
            return true;
        } else {
            delete saver_module;
            return false;
        }
    }

}
