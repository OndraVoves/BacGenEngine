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


#include "../include/babstracttexture.h"

namespace BackGenEngine {
    BoxE::Core::BAsciiString BAbstractTexture::textureFilter2string ( BAbstractTexture::ETextureFilterType type ) {
        switch ( type ) {
            case FT_BILINEAR:
                return "FT_BILINEAR";
                break;

            case FT_TRILINEAR:
                return "FT_TRILINEAR";
                break;
        }
    }

    BAbstractTexture::ETextureFilterType BAbstractTexture::string2textureFilter ( const BoxE::Core::BAsciiString &type ) {
        if ( type == "FT_TRILINEAR" ) {
            return FT_TRILINEAR;

        } else {

            return FT_BILINEAR;
        }
    }


    BAbstractTexture::BAbstractTexture ( ) : Width ( 0 ), Height ( 0 ), Mipmaping ( false ), eMinFilter ( MIN_Nearest ), eMagFilter ( MAG_Nearest ), eFilterType ( FT_BILINEAR ), InternalFormat ( TF_RGB ), ImageFormat ( TF_RGB ) {
    }

    BAbstractTexture::~BAbstractTexture() {

    }

    int BAbstractTexture::width( ) const {
        return Width;
    }

    int BAbstractTexture::height() const {
        return Height;
    }

    bool BAbstractTexture::isMipmapingEnable() const {
        return Mipmaping;
    }

    BAbstractTexture::ETextureMinFilter BAbstractTexture::minFilter() const {
        return eMinFilter;
    }

    BAbstractTexture::ETextureMagFilter BAbstractTexture::magFilter() const {
        return eMagFilter;
    }

    BAbstractTexture::ETexureFormat BAbstractTexture::internalFormat() const {
        return InternalFormat;
    }

    BAbstractTexture::ETexureFormat BAbstractTexture::imageFormat() const {
        return ImageFormat;
    }

    void BAbstractTexture::create ( int width, int height, bool mipmaping, ETextureMinFilter e_min_filter, ETextureMagFilter e_mag_filter, ETexureFormat e_internal_format, ETexureFormat e_image_format, const unsigned char *p_data ) {
        Width = width;
        Height = height;

        Mipmaping = mipmaping;
        eMinFilter = e_min_filter;
        eMagFilter = e_mag_filter;

        InternalFormat = e_internal_format;
        ImageFormat = e_image_format;
    }

    void BAbstractTexture::create ( int width, int height, bool mipmaping, ETextureFilterType e_filter_type, ETexureFormat e_internal_format, ETexureFormat e_image_format, const unsigned char *p_data ) {
        Width = width;
        Height = height;
        Mipmaping = mipmaping;

        eFilterType = e_filter_type;

        InternalFormat = e_internal_format;
        ImageFormat = e_image_format;
    }

}
