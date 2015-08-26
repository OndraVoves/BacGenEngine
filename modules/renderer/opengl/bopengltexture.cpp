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


#include "bopengltexture.h"

BOpenGLTexture::BOpenGLTexture() : BAbstractTexture( ), TextureID ( 0 ) {
    glGenTextures ( 1, &TextureID );
}

BOpenGLTexture::~BOpenGLTexture() {
    glDeleteTextures ( 1, &TextureID );
}


void BOpenGLTexture::create ( int width, int height, bool mipmaping, ETextureFilterType e_filter_type, ETexureFormat e_internal_format, ETexureFormat e_image_format, const unsigned char *p_data ) {
    ETextureMagFilter e_mag_filter = MAG_Linear;
    ETextureMinFilter e_min_filter = MIN_Linear;

    switch ( e_filter_type ) {
        case FT_BILINEAR:
            if ( mipmaping ) {
                e_min_filter = MIN_LinearMipmapNearest;
            } else {
                e_min_filter = MIN_Linear;
            }
            break;

        case FT_TRILINEAR:
            if ( mipmaping ) {
                e_min_filter = MIN_LinearMipmapLinear;
            } else {
                e_min_filter = MIN_Linear;
            }
            break;
    }

    create ( width, height, mipmaping, e_min_filter, e_mag_filter, e_internal_format, e_image_format, p_data );
    BAbstractTexture::create ( width, height, mipmaping, e_filter_type, e_internal_format, e_image_format, p_data  );
}

void BOpenGLTexture::create ( int width, int height, bool mipmaping, ETextureMinFilter e_min_filter, ETextureMagFilter e_mag_filter, ETexureFormat e_internal_format, ETexureFormat e_image_format, const unsigned char *p_data ) {
    GLboolean gl_mipmaping;

    if ( mipmaping ) {
        gl_mipmaping = GL_TRUE;
    } else {
        gl_mipmaping = GL_FALSE;
    }

    /* Format */
    GLenum format;
    GLint  internal_format;

    switch ( e_internal_format ) {
        case TF_RGB:
            internal_format = GL_RGB;
            break;

        case TF_RGBA:
            internal_format = GL_RGBA;
            break;

        case TF_RGB8:
            internal_format = GL_RGB8;
            break;

        case TF_RGBA8:
            internal_format = GL_RGBA8;
            break;
    }

    switch ( e_image_format ) {
        case TF_RGB:
            format = GL_RGB;
            break;

        case TF_RGBA:
            format = GL_RGBA;
            break;

        case TF_RGB8:
            format = GL_RGB8;
            break;

        case TF_RGBA8:
            format = GL_RGBA8;
            break;
    }


    /* Texture filtering. */
    GLfloat gl_mag_filter;
    GLfloat gl_min_filter;

    switch ( e_mag_filter ) {
        case MAG_Nearest :
            gl_mag_filter = GL_NEAREST;
            break;

        case MAG_Linear :
            gl_mag_filter = GL_LINEAR;
            break;
    }

    switch ( e_min_filter ) {
        case MIN_Nearest :
            gl_min_filter = GL_NEAREST;
            break;

        case MIN_Linear :
            gl_min_filter = GL_LINEAR;
            break;

        case MIN_NearestMipmapNearest :
            gl_min_filter = GL_NEAREST_MIPMAP_NEAREST;
            break;

        case MIN_NearestMipmapLinear :
            gl_min_filter = GL_NEAREST_MIPMAP_LINEAR;
            break;

        case MIN_LinearMipmapNearest :
            gl_min_filter = GL_LINEAR_MIPMAP_NEAREST;
            break;

        case MIN_LinearMipmapLinear :
            gl_min_filter = GL_LINEAR_MIPMAP_LINEAR;
            break;
    }

    glBindTexture ( GL_TEXTURE_2D, TextureID );

    glTexParameterf ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl_mag_filter );
    glTexParameterf ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl_min_filter );

    glTexParameteri ( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, gl_mipmaping );

    glTexImage2D ( GL_TEXTURE_2D, 0, internal_format, width, height, 0,
                   format, GL_UNSIGNED_BYTE, p_data );

    glBindTexture ( GL_TEXTURE_2D, 0 );

    BAbstractTexture::create ( width, height, mipmaping, e_min_filter, e_mag_filter, e_internal_format, e_image_format, p_data );

}