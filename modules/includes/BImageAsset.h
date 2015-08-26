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

#ifndef BIMAGEASSET_H
#define BIMAGEASSET_H

#include <BackGenEngine/babstractasset.h>
#include <BackGenEngine/bmodulesheader.h>
#include <BackGenEngine/babstractrenderer.h>

class BImageAsset : public BackGenEngine::BAbstractAsset {
    public:
        BImageAsset ( BackGenEngine::BProject *pc_project, BackGenEngine::BAbstractRenderer *pc_renderer, BackGenEngine::BLogger *pc_logger, BackGenEngine::BAbstractModuleSystem *module_system, BackGenEngine::BAssetManager *pc_asset_manager );
        virtual ~BImageAsset();

        virtual BoxE::Core::BAsciiString getAssetType() const {
            return "Image";
        }

        virtual BoxE::Core::BAsciiString getInterfaceType() const {
            return "Image";
        }

        int width() const {
            return Width;
        }

        int height( ) const {
            return Height;
        }

        int bpp() const {
            return BPP;
        }

        unsigned char *pixels( )  {
            return Pixels;
        }

        void width ( int w ) {
            Width = w;
        }

        void height ( int h ) {
            Height = h;
        }

        void bpp ( int b ) {
            BPP = b;
        }

        void pixels ( unsigned char *p )  {
            Pixels = p;
        }

    protected:
        virtual bool unload();

    private:
        int Width;
        int Height;
        int BPP;
        unsigned char *Pixels;
};


#endif /* BIMAGEASSET_H */
