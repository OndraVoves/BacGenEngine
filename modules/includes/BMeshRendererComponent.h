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

#ifndef BMESHRENDERERNCOMPONENT_H
#define BMESHRENDERERNCOMPONENT_H

#include <BoxE/BoxECore>

#include <BackGenEngine/brenderablecomponent.h>
#include <BackGenEngine/bmodulesheader.h>

class BMaterialAsset;

class BMeshRendererComponent : public BackGenEngine::BRenderableComponent {
        BGE_RTTI_DECLARATION
    public:
        BMeshRendererComponent ( BackGenEngine::BScene *pc_scene );
        virtual ~BMeshRendererComponent();

        virtual BoxE::Core::BAsciiString getName() const {
            return "MeshRenderer";
        }

        virtual void render();

        void setTiling ( const BoxE::Math::BVector2f &tiling );
        BoxE::Math::BVector2f getTiling( ) const;

        void setMaterialAsset ( BMaterialAsset *pc_asset );
        BMaterialAsset *getMaterialAsset();

        virtual BAbstractComponent *duplicate() const;

        virtual BoxE::Core::BByteArray toByteArray();
        virtual bool fromByteArray ( const BoxE::Core::BByteArray &byte_array,  BackGenEngine::BAssetManager *pc_asset_manager );
    private:
        BMaterialAsset *pcMaterialAsset;
        BoxE::Math::BMatrix4x4f TextureMatrix;
        BoxE::Math::BVector2f Tiling;

        void generateTextureMatrix();
};


#endif /* BMESHRENDERERNCOMPONENT_H */
