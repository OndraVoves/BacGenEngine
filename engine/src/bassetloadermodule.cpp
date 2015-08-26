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


#include "../include/bassetloadermodule.h"

namespace BackGenEngine {

    BAssetLoaderModule::BAssetLoaderModule ( BoxE::Core::BLibrary *library, const BoxE::Core::BAsciiString &asset_name ) : LoadFce ( 0 ), pLibrary ( library ), AssetName ( asset_name ) {
    }

    BAssetLoaderModule::~BAssetLoaderModule() {
    }

    const BoxE::Core::BAsciiString  &BAssetLoaderModule::getAssetType() const {
        return AssetName;
    }

    bool BAssetLoaderModule::load() {
        LoadFce =  ( load_fce_t * ) pLibrary->resolv ( "loadAsset" );
        if ( LoadFce == 0 ) {
            return false;
        }
        return true;
    }

    bool BAssetLoaderModule::load ( BAbstractAsset *asset, BoxE::Core::BIODevice *data, BAssetManager *pc_asset_manager, BLogger *pc_logger ) {
        if ( LoadFce != 0 ) {
            return LoadFce ( asset, data, pc_asset_manager, pc_logger );
        } else {
            return false;
        }
    }

}
