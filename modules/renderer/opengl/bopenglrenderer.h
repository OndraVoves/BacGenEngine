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


#ifndef BOPENGLRENDERER_H
#define BOPENGLRENDERER_H

#include <BackGenEngine/babstractrenderer.h>
#include <BackGenEngine/babstracttexture.h>

#include <GL/glew.h>

namespace BackGenEngine {
    class BAbstractFrameBuffer;
}

class BOpenGLRenderer : public BackGenEngine::BAbstractRenderer {
    public:
        BOpenGLRenderer ( BackGenEngine::BLogger *pc_logger );
        virtual ~BOpenGLRenderer();


        virtual void setMatrix ( ERendererMatrixType e_matrix_type, const BoxE::Math::BMatrix4x4f &rc_matrix );
        virtual void multMatrix ( ERendererMatrixType e_matrix_type, const BoxE::Math::BMatrix4x4f &rc_matrix );
        virtual void loadIdentityMatrix ( ERendererMatrixType e_matrix_type );

        virtual void setTextureMatrix ( int i, const BoxE::Math::BMatrix4x4f &rc_matrix );

        virtual void setPolyginType ( ERendererPolygonType type );

        virtual void init( );
        virtual void beginRender ( bool clean_color_buffer, bool clean_depth_buffer, const BoxE::Math::BVector3f &rc_color );
        virtual void endRender();

        virtual BackGenEngine::BAbstractTexture *createTexture ( int width, int height, bool mipmaping, BackGenEngine::BAbstractTexture::ETextureMinFilter e_min_filter, BackGenEngine::BAbstractTexture::ETextureMagFilter e_mag_filter, BackGenEngine::BAbstractTexture::ETexureFormat e_internal_format, BackGenEngine::BAbstractTexture::ETexureFormat e_image_format, const unsigned char *p_data );
        virtual BackGenEngine::BAbstractTexture *createTexture ( int width, int height, bool mipmaping, BackGenEngine::BAbstractTexture::ETextureFilterType e_texture_filter_type, BackGenEngine::BAbstractTexture::ETexureFormat e_internal_format, BackGenEngine::BAbstractTexture::ETexureFormat e_image_format, const unsigned char *p_data );
        virtual BackGenEngine::BAbstractTexture *createTexture();
        virtual void useTexture ( BackGenEngine::BAbstractTexture *pc_texture, int texture_unit );

        virtual BackGenEngine::BAbstractFrameBuffer *createFramebuffer() ;

        virtual void drawSreenTexture ( BackGenEngine::BAbstractTexture *pc_texture );

        virtual void renderVB ( ERendererPrimitiveType e_primitive_type, const BackGenEngine::BVertexBuffer &vertex_buffer, int *a_indexs_buffer, int primitive_count );

    public:
        virtual void onScreenChanged ( const BoxE::Math::BVector3f &rc_screen_resolution, bool fullscreen );

    private:
        BoxE::Math::BMatrix4x4f ScreenOrtho;
        GLenum GlewInitStatus;

};

#endif // BOPENGLRENDERER_H
