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


#include "../include/bassetsavermodule.h"

namespace BackGenEngine {
    BAssetSaverModule::BAssetSaverModule ( BoxE::Core::BLibrary *library ) : SaveFce ( 0 ), pLibrary ( library ) {
    }

    BAssetSaverModule::~BAssetSaverModule() {
    }

    bool BAssetSaverModule::load() {
        SaveFce =  ( save_fce_t * ) pLibrary->resolv ( "saveAsset" );
        if ( SaveFce == 0 ) {
            return false;
        }
        return true;
    }

    bool BAssetSaverModule::save ( BAbstractAsset *asset, BoxE::Core::BIODevice *data, BLogger *pc_logger ) {
        if ( SaveFce != 0 ) {
            return SaveFce ( asset, data, pc_logger );
        } else {
            return false;
        }
    }
}