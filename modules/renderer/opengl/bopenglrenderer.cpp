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

#include "bopenglrenderer.h"

#include <GL/glew.h>
#include <BackGenEngine/blogger.h>
#include <BackGenEngine/bvertex.h>
#include <BoxE/BVector3f>

#include <SDL/SDL.h>

#include "bopengltexture.h"
#include "bopenglframebuffer.h"


inline bool checkGLErrors (  BackGenEngine::BLogger *pc_logger, const BoxE::Core::BAsciiString &fce_name ) {
    GLenum error = glGetError( );

    switch ( error ) {
        case GL_NO_ERROR:
            return false;

        case GL_INVALID_ENUM:
            BGE_LOGGER_ERROR ( pc_logger, "BOpenGLRenderer", fce_name, "GL error: GL_INVALID_ENUM.\n" );
            break;

        case GL_INVALID_VALUE:
            BGE_LOGGER_ERROR ( pc_logger, "BOpenGLRenderer", fce_name, "GL error: GL_INVALID_VALUE.\n" );
            break;

        case GL_INVALID_OPERATION:
            BGE_LOGGER_ERROR ( pc_logger, "BOpenGLRenderer", fce_name, "GL error: GL_INVALID_OPERATION.\n" );
            break;

        case GL_STACK_OVERFLOW:
            BGE_LOGGER_ERROR ( pc_logger, "BOpenGLRenderer", fce_name, "GL error: GL_STACK_OVERFLOW.\n" );
            break;

        case GL_STACK_UNDERFLOW:
            BGE_LOGGER_ERROR ( pc_logger, "BOpenGLRenderer", fce_name, "GL error: GL_STACK_UNDERFLOW.\n" );
            break;

        case GL_OUT_OF_MEMORY:
            BGE_LOGGER_ERROR ( pc_logger, "BOpenGLRenderer", fce_name, "GL error: GL_OUT_OF_MEMORY.\n" );
            break;

        case GL_TABLE_TOO_LARGE:
            BGE_LOGGER_ERROR ( pc_logger, "BOpenGLRenderer", fce_name, "GL error: GL_TABLE_TOO_LARGE.\n" );
            break;
    }

    return true;
}


BOpenGLRenderer::BOpenGLRenderer ( BackGenEngine::BLogger *pc_logger ) : BAbstractRenderer ( pc_logger ), GlewInitStatus ( 1 ) {
}

BOpenGLRenderer::~BOpenGLRenderer() {
}

void BOpenGLRenderer::setMatrix ( ERendererMatrixType e_matrix_type, const BoxE::Math::BMatrix4x4f &rc_matrix ) {
    //// TODO: gl matrix mode se zmeni ale nevrati se na puvodni hodnut... mozna brutalni chyba... =P
    BAbstractRenderer::setMatrix ( e_matrix_type, rc_matrix );

    //glPushAttrib ( GL_TRANSFORM_BIT );
    switch ( e_matrix_type ) {
        case MT_WORLD:
            glMatrixMode ( GL_MODELVIEW );
            glLoadTransposeMatrixf ( ( float * ) &getMatrix ( MT_WORLD ) );
            break;

        case MT_PROJECTION:
            glMatrixMode ( GL_PROJECTION );
            glLoadTransposeMatrixf ( ( float * ) &getMatrix ( MT_PROJECTION ) );
            break;

        default:
            break;
    }
    //glPopAttrib();

    checkGLErrors ( logger(), "setMatrix" );
}

void BOpenGLRenderer::multMatrix ( ERendererMatrixType e_matrix_type, const BoxE::Math::BMatrix4x4f &rc_matrix ) {
    // TODO: gl matrix mode se zmeni ale nevrati se na puvodni hodnut... mozna brutalni chyba... =P
    BAbstractRenderer::multMatrix ( e_matrix_type, rc_matrix );

    glPushAttrib ( GL_TRANSFORM_BIT );
    switch ( e_matrix_type ) {
        case MT_WORLD:
            glMatrixMode ( GL_MODELVIEW );
            glLoadTransposeMatrixf ( ( float * ) &getMatrix ( MT_WORLD ) );
            break;

        case MT_PROJECTION:
            glMatrixMode ( GL_PROJECTION );
            glLoadTransposeMatrixf ( ( float * ) &getMatrix ( MT_PROJECTION ) );
            break;

        default:
            break;
    }
    glPopAttrib();

//    checkGLErrors ( "multMatrix()" );
    checkGLErrors ( logger(), "multMatrix" );
}


void BOpenGLRenderer::loadIdentityMatrix ( ERendererMatrixType e_matrix_type ) {
    // TODO: gl matrix mode se zmeni ale nevrati se na puvodni hodnut... mozna brutalni chyba... =P
    BAbstractRenderer::loadIdentityMatrix ( e_matrix_type );

    glPushAttrib ( GL_TRANSFORM_BIT );
    switch ( e_matrix_type ) {
        case MT_WORLD:
            glMatrixMode ( GL_MODELVIEW );
            //glLoadIdentity();
            glLoadTransposeMatrixf ( ( float * ) ( &getMatrix ( MT_WORLD ) ) );
            break;

        case MT_PROJECTION:
            glMatrixMode ( GL_PROJECTION );
            //glLoadIdentity();
            glLoadTransposeMatrixf ( ( float * ) ( &getMatrix ( MT_PROJECTION ) ) );
            break;

        default:
            break;
    }
    glPopAttrib();

    checkGLErrors ( logger(), "loadIdentityMatrix" );
}

void BOpenGLRenderer::setTextureMatrix ( int i, const BoxE::Math::BMatrix4x4f &rc_matrix ) {
    BAbstractRenderer::setTextureMatrix ( i, rc_matrix );
    glActiveTexture ( GL_TEXTURE0 + i );
    glMatrixMode ( GL_TEXTURE );
    glLoadTransposeMatrixf ( ( float * ) &getTextureMatrix ( i ) );
}

void BOpenGLRenderer::setPolyginType ( BOpenGLRenderer::ERendererPolygonType type ) {
    BAbstractRenderer::setPolyginType ( type );
    switch ( type ) {
        case BOpenGLRenderer::fill:
            glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
            break;

        case BOpenGLRenderer::line:
            glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
            break;
    }
}


void BOpenGLRenderer::init( ) {
    if ( GlewInitStatus != GLEW_OK )  {
        GlewInitStatus = glewInit( );
        if ( GlewInitStatus != GLEW_OK ) {
            BGE_LOGGER_INFO ( logger(), "BOpenGLRenderer", "init", "GLEW init [BAD]" );
        } else {
            BGE_LOGGER_INFO ( logger(), "BOpenGLRenderer", "init", "GLEW init [OK]" );
        }
    }

    glEnable ( GL_DEPTH_TEST );
    glDepthFunc ( GL_LEQUAL );

    glShadeModel ( GL_SMOOTH );
    glHint ( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    glLineWidth ( 2.0f );

    setPolyginType ( fill );

    glDisable ( GL_LIGHTING );
    glEnable ( GL_TEXTURE_2D );

    /* Init Culling. */
    glEnable ( GL_CULL_FACE );
    glFrontFace ( GL_CCW );
    glCullFace ( GL_BACK );


    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE  );
    glEnable ( GL_COLOR_MATERIAL );

    loadIdentityMatrix ( MT_PROJECTION );
    pushMatrix ( MT_PROJECTION );

    loadIdentityMatrix ( MT_WORLD );
    pushMatrix ( MT_WORLD );

    checkGLErrors ( logger(), "init" );
}

void BOpenGLRenderer::beginRender ( bool clean_color_buffer, bool clean_depth_buffer, const BoxE::Math::BVector3f &rc_color ) {
    glClearColor ( rc_color.x(), rc_color.y(), rc_color.z(), 0.0f );

    GLbitfield clear_mask = 0;
    if ( clean_color_buffer ) {
        clear_mask |= GL_COLOR_BUFFER_BIT;
    }

    if ( clean_depth_buffer ) {
        clear_mask |= GL_DEPTH_BUFFER_BIT;
    }

    glClear ( clear_mask );
    loadIdentityMatrix ( MT_WORLD );

//            BAbstractRenderer::beginRender ( clean_color_buffer, clean_depth_buffer, rc_color );
}

void BOpenGLRenderer::endRender() {
    glFinish( );
    glFlush( );
}


BackGenEngine::BAbstractTexture *BOpenGLRenderer::createTexture ( int width, int height, bool mipmaping, BackGenEngine::BAbstractTexture::ETextureMinFilter e_min_filter, BackGenEngine::BAbstractTexture::ETextureMagFilter e_mag_filter, BackGenEngine::BAbstractTexture::ETexureFormat e_internal_format, BackGenEngine::BAbstractTexture::ETexureFormat e_image_format, const unsigned char *p_data ) {
    BOpenGLTexture *pc_texture = new BOpenGLTexture();
    pc_texture->create ( width, height, mipmaping, e_min_filter, e_mag_filter, e_internal_format, e_image_format, p_data );
    return pc_texture;

}

BackGenEngine::BAbstractTexture *BOpenGLRenderer::createTexture ( int width, int height, bool mipmaping, BackGenEngine::BAbstractTexture::ETextureFilterType e_texture_filter_type, BackGenEngine::BAbstractTexture::ETexureFormat e_internal_format, BackGenEngine::BAbstractTexture::ETexureFormat e_image_format, const unsigned char *p_data ) {
    BOpenGLTexture *pc_texture = new BOpenGLTexture();
    pc_texture->create ( width, height, mipmaping, e_texture_filter_type, e_internal_format, e_image_format, p_data );
    return pc_texture;
}

BackGenEngine::BAbstractTexture *BOpenGLRenderer::createTexture() {
    return new BOpenGLTexture();
}

void BOpenGLRenderer::useTexture ( BackGenEngine::BAbstractTexture *pc_texture, int texture_unit ) {
    if ( !pc_texture ) {
        glActiveTexture ( GL_TEXTURE0 + texture_unit );
        glBindTexture ( GL_TEXTURE_2D, 0 );
        return;
    }

    BOpenGLTexture *pc_ogl_texture = static_cast< BOpenGLTexture * > ( pc_texture );

    glActiveTexture ( GL_TEXTURE0 + texture_unit );
    glBindTexture ( GL_TEXTURE_2D, pc_ogl_texture->openglID() );
}

BackGenEngine::BAbstractFrameBuffer *BOpenGLRenderer::createFramebuffer() {
    return new BOpenGLFrameBuffer();
}

void BOpenGLRenderer::drawSreenTexture ( BackGenEngine::BAbstractTexture *pc_texture ) {
    BoxE::Math::BVector3f screen = getScreenResolution();

    pushMatrix ( MT_PROJECTION );
    setMatrix ( MT_PROJECTION, ScreenOrtho );

    pushMatrix ( MT_WORLD );
    loadIdentityMatrix ( MT_WORLD );

    glColor3f ( 1.0f, 1.0f, 1.0f  );

    useTexture ( pc_texture, 0 );
    glMatrixMode ( GL_TEXTURE );
    glLoadIdentity();

    glBegin ( GL_TRIANGLES );
    glTexCoord2f ( 0.0f, 0.0f );
    glVertex2f ( 0.0f, 0.0f );

    glTexCoord2f ( 1.0f, 0.0f );
    glVertex2f ( screen.x(), 0.0f );

    glTexCoord2f ( 1.0f, 1.0f );
    glVertex2f ( screen.x(), screen.y() );

    glTexCoord2f ( 1.0f, 1.0f );
    glVertex2f ( screen.x(), screen.y() );

    glTexCoord2f ( 0.0f, 1.0f );
    glVertex2f ( 0.0f, screen.y() );

    glTexCoord2f ( 0.0f, 0.0f );
    glVertex2f ( 0.0f, 0.0f );
    glEnd();

    useTexture ( 0, 0 );

    popMatrix ( MT_PROJECTION );
    popMatrix ( MT_WORLD );
}

void BOpenGLRenderer::renderVB ( ERendererPrimitiveType e_primitive_type, const BackGenEngine::BVertexBuffer &vertex_buffer, int *a_indexs_buffer, int primitive_count ) {
    glEnableClientState ( GL_VERTEX_ARRAY );
    glVertexPointer ( 3, GL_FLOAT, sizeof ( BackGenEngine::BVertex ), ( float * ) &vertex_buffer.data() [0].getPosition() );

    glEnableClientState ( GL_NORMAL_ARRAY );
    glNormalPointer ( GL_FLOAT, sizeof ( BackGenEngine::BVertex ), ( float * ) &vertex_buffer.data() [0].getNormal( ) );

    glEnableClientState ( GL_TEXTURE_COORD_ARRAY );
    glTexCoordPointer ( 2, GL_FLOAT, sizeof ( BackGenEngine::BVertex ), ( float * ) &vertex_buffer.data() [0].getTexCoord( ) );

    glEnableClientState ( GL_COLOR_ARRAY );
    glColorPointer ( 4, GL_FLOAT, sizeof (  BackGenEngine::BVertex ), ( float * ) &vertex_buffer.data() [0].getColor( ) );

    /*    BackGenEngine::BVertexBuffer::ConstIterator it = vertex_buffer.constBegin();
        while( it != vertex_buffer.constEnd() ) {
            ++it;
        }*/

    switch ( e_primitive_type ) {
        case PT_POINTS:
            glDrawElements ( GL_POINTS, primitive_count, GL_UNSIGNED_INT, a_indexs_buffer );
            break;

        case PT_LINES:
            glDrawElements ( GL_LINES, primitive_count * 2, GL_UNSIGNED_INT, a_indexs_buffer );
            break;

        case PT_LINE_STRIP:
            glDrawElements ( GL_LINE_STRIP, primitive_count + 1, GL_UNSIGNED_INT, a_indexs_buffer );
            break;

        case PT_LINE_LOOP:
            glDrawElements ( GL_LINE_LOOP, primitive_count, GL_UNSIGNED_INT, a_indexs_buffer );
            break;

        case PT_TRIANGLES:
            glDrawElements ( GL_TRIANGLES, primitive_count * 3, GL_UNSIGNED_INT, a_indexs_buffer );
            break;

        case PT_TRIANGLES_STRIP:
            glDrawElements ( GL_TRIANGLE_STRIP, primitive_count + 2, GL_UNSIGNED_INT, a_indexs_buffer );
            break;

        case PT_TRIANGLES_FAN:
            glDrawElements ( GL_TRIANGLE_FAN, primitive_count + 2, GL_UNSIGNED_INT, a_indexs_buffer );
            break;

        case PT_QUADS:
            glDrawElements ( GL_QUADS, primitive_count * 4, GL_UNSIGNED_INT, a_indexs_buffer );
            break;

        case PT_QUADS_STRIP:
            glDrawElements ( GL_QUAD_STRIP, ( primitive_count * 2 ) + 2, GL_UNSIGNED_INT, a_indexs_buffer );
            break;

        case PT_POLYGON:
            glDrawElements ( GL_POLYGON, primitive_count, GL_UNSIGNED_INT, a_indexs_buffer );
            break;
    }

    glDisableClientState ( GL_COLOR_ARRAY );
    glDisableClientState ( GL_TEXTURE_COORD_ARRAY );
    glDisableClientState ( GL_NORMAL_ARRAY );
    glDisableClientState ( GL_VERTEX_ARRAY );

    checkGLErrors ( logger(), "renderVB" );
}

void BOpenGLRenderer::onScreenChanged ( const BoxE::Math::BVector3f &rc_screen_resolution, bool fullscreen ) {
    BAbstractRenderer::onScreenChanged ( rc_screen_resolution, fullscreen );
    glViewport ( 0, 0, rc_screen_resolution.x(), rc_screen_resolution.y() );
    ScreenOrtho.setOrthographic (  0, rc_screen_resolution.x(), 0, rc_screen_resolution.y(), 0.0f, 1.0f );
    //checkGLErrors ( "onScreenChanged( )" );
}

