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


#include "../include/bproject.h"

#include "../include/blogger.h"

#include <BoxE/BIODevice>

namespace BackGenEngine {

    BProject::BProject ( BAbstractWindow *window, BAbstractModuleSystem *module_system, BLogger *logger ) : SceneManager ( logger ), Window ( window ),  ModuleSystem ( module_system ), AssetManager ( this, logger ), Logger ( logger ) {
    }

    BProject::~BProject( ) {
    }

    BoxE::Core::BAsciiString BProject::getName() const {
        return Name;
    }

    BoxE::Core::BAsciiString BProject::getBaseDir(  ) const {
        return BaseDir;
    }

    void BProject::setName ( const BoxE::Core::BAsciiString &name ) {
        Name = name;
    }

    void BProject::setBaseDir ( const BoxE::Core::BAsciiString &dir ) {
        BaseDir = dir;
    }

    BSceneManager &BProject::getSceneManager( ) {
        return SceneManager;
    }

    BAbstractModuleSystem *BProject::getModuleSystem() {
        return ModuleSystem;
    }

    BAssetManager &BProject::getAssetManager() {
        return AssetManager;
    }

    BoxE::Core::BByteArray BProject::toByteArray() {
        BoxE::Core::BAsciiString str ( "project {\n"
                                       "\tname %1\n"
                                       "}\n" );

        str.replace ( "%1", Name );

        return str;
    }

    bool BProject::fromByteArray ( const BoxE::Core::BByteArray &byte_array ) {
        BoxE::Core::BByteArray data ( byte_array );

        data.replace ( "\n", BoxE::Core::BByteArray ( " " ) );
        data.replace ( "\t", BoxE::Core::BByteArray ( "" ) );

        BoxE::Core::BLinkedList< BoxE::Core::BByteArray > list = data.split ( ' ' );

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
            if ( ( *it ) == "project" ) {
                ++it;
                if ( ( *it ) == "{" ) {
                    while ( it != list.constEnd() ) {
                        ++it;
                        if ( ( *it ) == "}" ) {
                            return true;
                        } else if ( ( *it ) == "name" ) {
                            if ( ( ++it ) == list.constEnd() ) {
                                return false;
                            }

                            setName ( *it );

                        }
                    }
                } else {
                    return false;
                }
            }
            ++it;
        }
    }

}