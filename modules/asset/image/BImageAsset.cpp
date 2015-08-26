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

#include "./BImageAsset.h"

#include <BackGenEngine/blogger.h>
#include <BackGenEngine/babstractmodulesystem.h>
#include <BackGenEngine/bproject.h>

BImageAsset::BImageAsset ( BackGenEngine::BProject *pc_project, BackGenEngine::BAbstractRenderer *pc_renderer, BackGenEngine::BLogger *pc_logger, BackGenEngine::BAbstractModuleSystem *module_system, BackGenEngine::BAssetManager *pc_asset_manager )
    : BAbstractAsset ( pc_project, pc_renderer, pc_logger, module_system, pc_asset_manager ), Width ( 0 ), Height ( 0 ), BPP ( 0 ), Pixels ( 0 ) {
}

BImageAsset::~BImageAsset() {
}


bool BImageAsset::unload() {
}

extern "C" {
    BASE_MODULE_HEADER ( BackGenEngine::ASSET, "Image", "0.0.1", "Ondra Voves" );

    BackGenEngine::BAbstractAsset *createAsset ( BackGenEngine::BProject *pc_project, BackGenEngine::BAbstractRenderer *pc_renderer, BackGenEngine::BLogger *pc_logger, BackGenEngine::BAbstractModuleSystem *module_system, BackGenEngine::BAssetManager *pc_asset_manager ) {
        return new BImageAsset ( pc_project, pc_renderer, pc_logger, module_system, pc_asset_manager );
    }
}
