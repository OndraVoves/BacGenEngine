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

#ifndef BTEXTUREASSET_H
#define BTEXTUREASSET_H

#include <BackGenEngine/babstractasset.h>
#include <BackGenEngine/bmodulesheader.h>
#include <BackGenEngine/babstracttexture.h>
#include <BackGenEngine/babstractrenderer.h>

#include "../image/BImageAsset.h"

class BTextureAsset : public BackGenEngine::BAbstractAsset {
    public:
        BTextureAsset ( BackGenEngine::BProject *pc_project, BackGenEngine::BAbstractRenderer *pc_renderer, BackGenEngine::BLogger *pc_logger, BackGenEngine::BAbstractModuleSystem *module_system, BackGenEngine::BAssetManager *pc_asset_manager );
        virtual ~BTextureAsset();

        virtual BoxE::Core::BAsciiString getAssetType() const {
            return "Texture";
        }

        virtual BoxE::Core::BAsciiString getInterfaceType() const {
            return "Texture";
        }

        BackGenEngine::BAbstractTexture *getTexture();

        BImageAsset *getImage();
        void setImage ( BImageAsset *pc_image );

        void setFilterType ( BackGenEngine::BAbstractTexture::ETextureFilterType e_filter_type  );
        BackGenEngine::BAbstractTexture::ETextureFilterType getFilterType() const;

        void setMipmaping ( bool mipmaping );
        bool getMipmaping( ) const;



        bool generateTexture();

    protected:
        virtual bool load();
        virtual bool unload();

    private:
        BackGenEngine::BAbstractRenderer *pcRenderer;
        BackGenEngine::BAbstractTexture *pcTexture;
        BImageAsset *pcImage;

        bool Mipmaping;
        BackGenEngine::BAbstractTexture::ETextureFilterType eFilterType;

        void onImageRelaoaded();
};


#endif /* BTEXTUREASSET_H */
