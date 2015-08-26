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

#include "./BTextureAsset.h"

BTextureAsset::BTextureAsset ( BackGenEngine::BProject *pc_project, BackGenEngine::BAbstractRenderer *pc_renderer, BackGenEngine::BLogger *pc_logger, BackGenEngine::BAbstractModuleSystem *module_system, BackGenEngine::BAssetManager *pc_asset_manager  ) : BAbstractAsset ( pc_project, pc_renderer, pc_logger, module_system, pc_asset_manager  ), pcRenderer ( pc_renderer ), pcTexture ( 0 ), pcImage ( 0 ), Mipmaping ( false ), eFilterType ( BackGenEngine::BAbstractTexture::FT_BILINEAR ) {
}

BTextureAsset::~BTextureAsset() {
}

BackGenEngine::BAbstractTexture *BTextureAsset::getTexture() {
    return pcTexture;
}

BImageAsset *BTextureAsset::getImage() {
    return pcImage;
}

void BTextureAsset::setImage ( BImageAsset *pc_image ) {
    if ( pcImage ) {
        pcImage->onReload().disconnect ( this, &BTextureAsset::onImageRelaoaded  );
    }

    pcImage = pc_image;

    if ( pc_image ) {
        pc_image->onReload().connect ( this, &BTextureAsset::onImageRelaoaded  );
    }
}


void BTextureAsset::setFilterType ( BackGenEngine::BAbstractTexture::ETextureFilterType e_filter_type  ) {
    eFilterType = e_filter_type;
}

BackGenEngine::BAbstractTexture::ETextureFilterType BTextureAsset::getFilterType() const {
    return eFilterType;
}

void BTextureAsset::setMipmaping ( bool mipmaping ) {
    Mipmaping = mipmaping;
}

bool BTextureAsset::getMipmaping( ) const {
    return Mipmaping;
}


bool BTextureAsset::generateTexture() {
    if ( pcImage ) {
        pcImage->use();

        BackGenEngine::BAbstractTexture::ETexureFormat internal_format;
        BackGenEngine::BAbstractTexture::ETexureFormat image_format;

        switch ( pcImage->bpp() ) {
            case 24:
                internal_format = BackGenEngine::BAbstractTexture::TF_RGB;
                image_format = BackGenEngine::BAbstractTexture::TF_RGB;
                break;

            case 32:
                internal_format = BackGenEngine::BAbstractTexture::TF_RGBA;
                image_format = BackGenEngine::BAbstractTexture::TF_RGBA;
                break;
        }

        pcTexture =  pcRenderer->createTexture ( pcImage->width(), pcImage->height(), Mipmaping, eFilterType, internal_format, image_format, pcImage->pixels() );
        pcImage->unuse();

    } else {
        pcTexture =  pcRenderer-> createTexture();
    }

}

bool BTextureAsset::load() {
    if ( BAbstractAsset::load() ) {
        generateTexture();
    }
}

bool BTextureAsset::unload() {
}

void BTextureAsset::onImageRelaoaded() {
    generateTexture();
}

extern "C" {
    BASE_MODULE_HEADER ( BackGenEngine::ASSET, "Texture", "0.0.1", "Ondra Voves" );

    BackGenEngine::BAbstractAsset *createAsset ( BackGenEngine::BProject *pc_project, BackGenEngine::BAbstractRenderer *pc_renderer, BackGenEngine::BLogger *pc_logger, BackGenEngine::BAbstractModuleSystem *module_system, BackGenEngine::BAssetManager *pc_asset_manager ) {
        return new BTextureAsset ( pc_project, pc_renderer, pc_logger, module_system, pc_asset_manager );
    }
}
