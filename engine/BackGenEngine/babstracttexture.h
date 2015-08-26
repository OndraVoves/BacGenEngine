/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2011  Ondra Voves <email>

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


#ifndef BABSTRACTTEXTURE_H
#define BABSTRACTTEXTURE_H

#include <BoxE/BAsciiString>

namespace BackGenEngine {
    class BAbstractTexture {
        public:
            typedef enum {
                MAG_Nearest = 0,
                MAG_Linear
            } ETextureMagFilter;

            typedef enum {
                MIN_Nearest = 0,
                MIN_Linear,
                MIN_NearestMipmapNearest,
                MIN_NearestMipmapLinear,
                MIN_LinearMipmapNearest,
                MIN_LinearMipmapLinear
            } ETextureMinFilter;

            typedef enum {
                FT_BILINEAR = 0,
                FT_TRILINEAR
            } ETextureFilterType;

            static BoxE::Core::BAsciiString textureFilter2string ( ETextureFilterType type );
            static ETextureFilterType string2textureFilter ( const BoxE::Core::BAsciiString &type );

            typedef enum {
                TF_RGB = 0,
                TF_RGBA,
                TF_RGB8,
                TF_RGBA8
            } ETexureFormat;

        public:
            BAbstractTexture ( );
            virtual ~BAbstractTexture();

            int width( ) const;

            int height() const;

            bool isMipmapingEnable() const;

            ETextureMinFilter minFilter() const;

            ETextureMagFilter magFilter() const;

            ETexureFormat internalFormat() const;

            ETexureFormat imageFormat() const;

            virtual void create ( int width, int height, bool mipmaping, ETextureMinFilter e_min_filter, ETextureMagFilter e_mag_filter, ETexureFormat e_internal_format, ETexureFormat e_image_format, const unsigned char *p_data );
            virtual void create ( int width, int height, bool mipmaping, ETextureFilterType e_filter_type, ETexureFormat e_internal_format, ETexureFormat e_image_format, const unsigned char *p_data );


        private:
            int Width;
            int Height;

            bool Mipmaping;

            ETextureMinFilter eMinFilter;
            ETextureMagFilter eMagFilter;
            ETextureFilterType eFilterType;

            ETexureFormat InternalFormat;
            ETexureFormat ImageFormat;

    };
}

#endif // BABSTRACTTEXTURE_H
