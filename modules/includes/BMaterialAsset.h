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

#ifndef BMATERIALASSET_H
#define BMATERIALASSET_H

#include <BackGenEngine/babstractasset.h>
#include <BackGenEngine/bmodulesheader.h>
#include <BackGenEngine/babstracttexture.h>
#include <BackGenEngine/babstractrenderer.h>

#include <BTextureAsset.h>

class BMaterialAsset : public BackGenEngine::BAbstractAsset {
    public:
        BMaterialAsset ( BackGenEngine::BProject *pc_project, BackGenEngine::BAbstractRenderer *pc_renderer, BackGenEngine::BLogger *pc_logger, BackGenEngine::BAbstractModuleSystem *module_system, BackGenEngine::BAssetManager *pc_asset_manager  );
        virtual ~BMaterialAsset();

        virtual BoxE::Core::BAsciiString getAssetType() const {
            return "Material";
        }

        virtual BoxE::Core::BAsciiString getInterfaceType() const {
            return "Material";
        }

        BTextureAsset *getTextureUnit ( int i );
        void setTextureUnit ( int i, BTextureAsset *pc_texture );


        void begin();
        void end();

    protected:
        virtual bool unload();

    private:
        BackGenEngine::BAbstractRenderer *pcRenderer;
        BTextureAsset *aTextureUnit[4];
};


#endif /* BMATERIALASSET_H */
