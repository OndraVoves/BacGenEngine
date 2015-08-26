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


#include "bopenglframebuffer.h"

#include "./bopengltexture.h"

BOpenGLFrameBuffer::BOpenGLFrameBuffer() : BAbstractFrameBuffer(), FBOID ( 0 ) {
    glGenFramebuffers ( 1, &FBOID );
}

BOpenGLFrameBuffer::~BOpenGLFrameBuffer() {
    glDeleteFramebuffers ( 1, &FBOID );
}

GLuint BOpenGLFrameBuffer::openGLID() const {
    return FBOID;
}

void BOpenGLFrameBuffer::attachColor0Texture ( BackGenEngine::BAbstractTexture *pc_texture ) {
    begin();
    glFramebufferTexture2D ( GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
                             GL_TEXTURE_2D, static_cast< BOpenGLTexture * > ( pc_texture )->openglID(), 0 );
    GLuint depth_rb;
    glGenRenderbuffersEXT ( 1, &depth_rb );
    glBindRenderbufferEXT ( GL_RENDERBUFFER_EXT, depth_rb );
    glRenderbufferStorageEXT ( GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, pc_texture->width(), pc_texture->height() );
    glFramebufferRenderbufferEXT ( GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depth_rb );
    end();
}

void BOpenGLFrameBuffer::begin() {
    glBindFramebuffer ( GL_FRAMEBUFFER_EXT, FBOID );
}

void BOpenGLFrameBuffer::end() {
    glBindFramebuffer ( GL_FRAMEBUFFER_EXT, 0 );
}
