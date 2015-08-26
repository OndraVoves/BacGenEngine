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


#ifndef BOPENGLTEXTURE_H
#define BOPENGLTEXTURE_H

#include <GL/glew.h>

#include <BackGenEngine/babstracttexture.h>


class BOpenGLTexture : public BackGenEngine::BAbstractTexture  {
    public:
        BOpenGLTexture();
        ~BOpenGLTexture();

        GLuint openglID() const {
            return TextureID;
        }


        virtual void create ( int width, int height, bool mipmaping, ETextureFilterType e_filter_type, ETexureFormat e_internal_format, ETexureFormat e_image_format, const unsigned char *p_data );
        virtual void create ( int width, int height, bool mipmaping, ETextureMinFilter e_min_filter, ETextureMagFilter e_mag_filter, ETexureFormat e_internal_format, ETexureFormat e_image_format, const unsigned char *p_data );

    private:
        GLuint TextureID;
};

#endif // BOPENGLTEXTURE_H
