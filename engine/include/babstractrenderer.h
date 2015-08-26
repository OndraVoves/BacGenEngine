/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#ifndef BABSTRACTRENDERER_H
#define BABSTRACTRENDERER_H

#include <BoxE/BStack>

#include <BoxE/BoxECore>

#include "bvertexbuffer.h"

#include "babstracttexture.h"

namespace BackGenEngine {
    class BLogger;
    class BAbstractFrameBuffer;
}


namespace BackGenEngine {

    class BAbstractRenderer {
        public:
            /*!
             * Matrix type enum.
             */
            typedef enum ERendererMatrixType {
                MT_WORLD = 0, //!< World matrix.
                MT_PROJECTION, //!< Projection matrix.
                MT_LAST
            } ERendererMatrixType;

            /*!
             * Primitive type enum.
             */
            typedef enum ERendererPrimitiveType {
                PT_POINTS = 0,      //!< Points.
                PT_LINES,           //!< Lines.
                PT_LINE_STRIP,      //!< Line strip.
                PT_LINE_LOOP,       //!< Line loop.
                PT_TRIANGLES,       //!< Triangles.
                PT_TRIANGLES_STRIP, //!< Triangles strip.
                PT_TRIANGLES_FAN,   //!< Triangles fan.
                PT_QUADS,           //!< Quads.
                PT_QUADS_STRIP,     //!< Quads strip.
                PT_POLYGON          //!< Polygon.
            } ERendererPrimitiveType;

            typedef enum ERendererPolygonType {
                fill = 0,
                line
            };

        public:
            BAbstractRenderer ( BLogger *pc_logger );
            virtual ~BAbstractRenderer();

            const BoxE::Math::BVector3f &getScreenResolution() const;

            virtual void setMatrix ( ERendererMatrixType e_matrix_type, const BoxE::Math::BMatrix4x4f &rc_matrix );
            const BoxE::Math::BMatrix4x4f &getMatrix ( ERendererMatrixType e_matrix_type ) const;

            virtual void multMatrix ( ERendererMatrixType e_matrix_type, const BoxE::Math::BMatrix4x4f &rc_matrix );
            virtual void loadIdentityMatrix ( ERendererMatrixType e_matrix_type );
            virtual void pushMatrix ( ERendererMatrixType e_matrix_type );
            virtual void popMatrix ( ERendererMatrixType e_matrix_type );

            const BoxE::Math::BMatrix4x4f &getTextureMatrix ( int i );
            virtual void setTextureMatrix ( int i, const BoxE::Math::BMatrix4x4f &rc_matrix );
            virtual void multTextureMatrix ( int unit, const BoxE::Math::BMatrix4x4f &rc_matrix );
            virtual void loadIdentityTextureMatrix ( int unit );
            virtual void pushTextureMatrix ( int unit );
            virtual void popTextureMatrix ( int unit );

            virtual void setPolyginType ( ERendererPolygonType type );
            ERendererPolygonType getPolygonType() const;

            virtual void init( ) = 0;
            virtual void beginRender ( bool clean_color_buffer, bool clean_depth_buffer, const BoxE::Math::BVector3f &rc_color ) = 0;
            virtual void endRender() = 0;

            virtual BAbstractTexture *createTexture ( int width, int height, bool mipmaping, BAbstractTexture::ETextureMinFilter e_min_filter, BAbstractTexture::ETextureMagFilter e_mag_filter, BAbstractTexture::ETexureFormat e_internal_format, BAbstractTexture::ETexureFormat e_image_format, const unsigned char *p_data ) = 0;
            virtual BAbstractTexture *createTexture ( int width, int height, bool mipmaping, BAbstractTexture::ETextureFilterType e_texture_filter_type, BAbstractTexture::ETexureFormat e_internal_format, BAbstractTexture::ETexureFormat e_image_format, const unsigned char *p_data ) = 0;
            virtual BAbstractTexture *createTexture() = 0;
            virtual void useTexture ( BAbstractTexture *pc_texture, int texture_unit ) = 0;

            virtual BAbstractFrameBuffer *createFramebuffer() = 0;

            virtual void drawSreenTexture ( BAbstractTexture *pc_texture ) = 0;

            virtual void renderVB ( ERendererPrimitiveType e_primitive_type, const BVertexBuffer &vertex_buffer, int *a_indexs_buffer, int primitive_count ) = 0;

        public:
            virtual void onScreenChanged ( const BoxE::Math::BVector3f &rc_screen_resolution, bool fullscreen );

        protected:
            BLogger *logger();

        private:
            BLogger *pcLogger;

            BoxE::Math::BMatrix4x4f aMatrixs[ MT_LAST ];
            BoxE::Core::BStack<BoxE::Math::BMatrix4x4f> aMatrixsStack[ MT_LAST ];

            BoxE::Math::BMatrix4x4f aTextureMatrixs[4];
            BoxE::Core::BStack<BoxE::Math::BMatrix4x4f> aTextureMatrixsStack[4];

            ERendererPolygonType ePlygonType;

            //todo 2f
            BoxE::Math::BVector3f ScreenResolution;
    };

}
#endif // BABSTRACTRENDERER_H
