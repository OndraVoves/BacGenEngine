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

#include "./BMaterialAsset.h"

BMaterialAsset::BMaterialAsset ( BackGenEngine::BProject *pc_project, BackGenEngine::BAbstractRenderer *pc_renderer, BackGenEngine::BLogger *pc_logger, BackGenEngine::BAbstractModuleSystem *module_system, BackGenEngine::BAssetManager *pc_asset_manager  ) : BAbstractAsset ( pc_project, pc_renderer, pc_logger, module_system, pc_asset_manager ), pcRenderer ( pc_renderer )  {
    aTextureUnit[ 0 ] = 0;
    aTextureUnit[ 1 ] = 0;
    aTextureUnit[ 2 ] = 0;
    aTextureUnit[ 3 ] = 0;
}

BMaterialAsset::~BMaterialAsset() {
}

BTextureAsset *BMaterialAsset::getTextureUnit ( int i ) {
    if ( ( i < 0 )  && ( i < 4 ) ) {
        return 0;
    }

    return aTextureUnit[i];
}

void BMaterialAsset::setTextureUnit ( int i, BTextureAsset *pc_texture ) {
    if ( ( i < 0 )  && ( i < 4 ) ) {
        return;
    }

    aTextureUnit[i] = pc_texture;
}

void BMaterialAsset::begin() {
    if ( aTextureUnit[0] ) {
        aTextureUnit[0]->use();
        pcRenderer->useTexture ( aTextureUnit[0]->getTexture() , 0 );
        aTextureUnit[0]->unuse();
    } else {
        pcRenderer->useTexture ( 0 , 0 );
    }

    if ( aTextureUnit[1] ) {
        aTextureUnit[1]->use();
        pcRenderer->useTexture ( aTextureUnit[1]->getTexture() , 1 );
        aTextureUnit[1]->unuse();
    } else {
        pcRenderer->useTexture ( 0 , 1 );
    }

    if ( aTextureUnit[2] ) {
        aTextureUnit[2]->use();
        pcRenderer->useTexture ( aTextureUnit[2]->getTexture() , 2 );
        aTextureUnit[2]->unuse();
    } else {
        pcRenderer->useTexture ( 0 , 2 );
    }


    if ( aTextureUnit[3] ) {
        aTextureUnit[3]->use();
        pcRenderer->useTexture ( aTextureUnit[3]->getTexture() , 3 );
        aTextureUnit[3]->unuse();
    } else {
        pcRenderer->useTexture ( 0 , 3 );
    }

}

void BMaterialAsset::end() {
    pcRenderer->useTexture ( 0, 0 );
    pcRenderer->useTexture ( 0, 1 );
    pcRenderer->useTexture ( 0, 2 );
    pcRenderer->useTexture ( 0, 3 );
}

bool BMaterialAsset::unload() {
}

extern "C" {
    BASE_MODULE_HEADER ( BackGenEngine::ASSET, "Material", "0.0.1", "Ondra Voves" );

    BackGenEngine::BAbstractAsset *createAsset ( BackGenEngine::BProject *pc_project, BackGenEngine::BAbstractRenderer *pc_renderer, BackGenEngine::BLogger *pc_logger, BackGenEngine::BAbstractModuleSystem *module_system, BackGenEngine::BAssetManager *pc_asset_manager ) {
        return new BMaterialAsset ( pc_project, pc_renderer, pc_logger, module_system, pc_asset_manager );
    }
}