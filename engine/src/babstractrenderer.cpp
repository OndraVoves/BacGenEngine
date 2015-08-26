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

#include "../include/babstractrenderer.h"

namespace BackGenEngine {

    BAbstractRenderer::BAbstractRenderer ( BLogger *pc_logger ) : pcLogger ( pc_logger ) {
        for ( int i = 0; i < MT_LAST; i++ ) {
            aMatrixs[i].setToIdentity();
        }

        for ( int i = 0; i < 4; i++ ) {
            aTextureMatrixs[i].setToIdentity();
        }
    }

    BAbstractRenderer::~BAbstractRenderer() {
    }


    const BoxE::Math::BVector3f &BAbstractRenderer::getScreenResolution() const {
        return ScreenResolution;
    }

    void BAbstractRenderer::setMatrix ( ERendererMatrixType e_matrix_type, const BoxE::Math::BMatrix4x4f &rc_matrix ) {
        aMatrixs[ e_matrix_type ] = rc_matrix ;
    }

    const BoxE::Math::BMatrix4x4f &BAbstractRenderer::getMatrix ( ERendererMatrixType e_matrix_type ) const {
        return aMatrixs[ e_matrix_type ];
    }


    void BAbstractRenderer::multMatrix ( ERendererMatrixType e_matrix_type, const BoxE::Math::BMatrix4x4f &rc_matrix ) {
        aMatrixs[ e_matrix_type ] = aMatrixs[ e_matrix_type ] * rc_matrix;
    }


    void BAbstractRenderer::loadIdentityMatrix ( ERendererMatrixType e_matrix_type ) {
        aMatrixs[ e_matrix_type ].setToIdentity();
    }


    void BAbstractRenderer::pushMatrix ( ERendererMatrixType e_matrix_type ) {
        aMatrixsStack[ e_matrix_type ].push ( aMatrixs[ e_matrix_type ] );
    }

    void BAbstractRenderer::popMatrix ( ERendererMatrixType e_matrix_type ) {
        setMatrix ( e_matrix_type, aMatrixsStack[ e_matrix_type ].pop() );
    }

    const BoxE::Math::BMatrix4x4f   &BAbstractRenderer::getTextureMatrix ( int i ) {
        return aTextureMatrixs[i];
    }

    void BAbstractRenderer::setTextureMatrix ( int i, const BoxE::Math::BMatrix4x4f &rc_matrix ) {
        aTextureMatrixs[i] = rc_matrix;
    }

    void BAbstractRenderer::multTextureMatrix ( int unit, const BoxE::Math::BMatrix4x4f &rc_matrix ) {
        aTextureMatrixs[unit] *= rc_matrix;
    }

    void BAbstractRenderer::loadIdentityTextureMatrix ( int unit ) {
        setTextureMatrix ( unit, BoxE::Math::BMatrix4x4f::IDENTITY );
    }

    void BAbstractRenderer::pushTextureMatrix ( int unit ) {
        aTextureMatrixsStack[ unit ].push ( aTextureMatrixs[unit ] );
    }

    void BAbstractRenderer::popTextureMatrix ( int unit ) {
        setTextureMatrix ( unit, aTextureMatrixsStack[ unit ].pop() );
    }

    void BAbstractRenderer::setPolyginType ( BAbstractRenderer::ERendererPolygonType type ) {
        ePlygonType = type;
    }

    BAbstractRenderer::ERendererPolygonType BAbstractRenderer::getPolygonType() const {
        return ePlygonType;
    }

    BLogger *BAbstractRenderer::logger() {
        return pcLogger;
    }

    void BAbstractRenderer::onScreenChanged ( const BoxE::Math::BVector3f &rc_screen_resolution, bool fullscreen ) {
        ScreenResolution = rc_screen_resolution;
    }

}
