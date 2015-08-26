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

#include "./BCubeMesh.h"

#include <BackGenEngine/bobject.h>
#include <BackGenEngine/bscene.h>

BGE_RTTI_IMPLEMENTATION ( BackGenEngine, BCubeMesh, BAbstractMesh );

BCubeMesh::BCubeMesh (  BackGenEngine::BScene *pc_scene ) : BAbstractMesh ( pc_scene ) {
    aIndexBuffer = new int[ 36 ]; // TODO: MALLOC

    // Front
    aIndexBuffer[0] = 0;
    aIndexBuffer[1] = 1;
    aIndexBuffer[2] = 2;
    aIndexBuffer[3] = 2;
    aIndexBuffer[4] = 3;
    aIndexBuffer[5] = 0;

    // Back
    aIndexBuffer[6] = 5;
    aIndexBuffer[7] = 4;
    aIndexBuffer[8] = 7;
    aIndexBuffer[9] = 7;
    aIndexBuffer[10] = 6;
    aIndexBuffer[11] = 5;

    // Top
    aIndexBuffer[12] = 8;
    aIndexBuffer[13] = 9;
    aIndexBuffer[14] = 10;
    aIndexBuffer[15] = 10;
    aIndexBuffer[16] = 11;
    aIndexBuffer[17] = 8;

    // Bottom
    aIndexBuffer[18] = 13;
    aIndexBuffer[19] = 12;
    aIndexBuffer[20] = 15;
    aIndexBuffer[21] = 15;
    aIndexBuffer[22] = 14;
    aIndexBuffer[23] = 13;

    // Left
    aIndexBuffer[24] = 16;
    aIndexBuffer[25] = 17;
    aIndexBuffer[26] = 18;
    aIndexBuffer[27] = 18;
    aIndexBuffer[28] = 19;
    aIndexBuffer[29] = 16;

    // Right
    aIndexBuffer[30] = 21;
    aIndexBuffer[31] = 20;
    aIndexBuffer[32] = 23;
    aIndexBuffer[33] = 23;
    aIndexBuffer[34] = 22;
    aIndexBuffer[35] = 21;

    VertexBuffer.resize ( 24 );

    setSize ( 1.0f );
}

BCubeMesh::~BCubeMesh( ) {
    delete [] aIndexBuffer;
}

BackGenEngine::BVertexBuffer *BCubeMesh::getVertexBuffer() {
    return &VertexBuffer;
}

int *BCubeMesh::getIndexBuffer() {
    return aIndexBuffer;
}

void BCubeMesh::setSize ( int size ) {
    if ( size == 0 ) {
        return; // TODO
    }

    Size = size;
    float half_size = Size * 0.5f;

    // Front
    VertexBuffer[0].getPosition() = BoxE::Math::BVector3f ( -half_size, -half_size, half_size );
    VertexBuffer[0].getTexCoord() = BoxE::Math::BVector2f ( 0.0f, 0.0f ) ;

    VertexBuffer[1].getPosition() = BoxE::Math::BVector3f ( half_size, -half_size, half_size );
    VertexBuffer[1].getTexCoord() = BoxE::Math::BVector2f ( 1.0f, 0.0f ) ;

    VertexBuffer[2].getPosition() = BoxE::Math::BVector3f ( half_size, half_size, half_size ) ;
    VertexBuffer[2].getTexCoord() = BoxE::Math::BVector2f ( 1.0f, 1.0f ) ;

    VertexBuffer[3].getPosition() = BoxE::Math::BVector3f ( -half_size, half_size, half_size ) ;
    VertexBuffer[3].getTexCoord() = BoxE::Math::BVector2f ( 0.0f, 1.0f ) ;

    // Back
    VertexBuffer[4].getPosition() = BoxE::Math::BVector3f ( -half_size, -half_size, -half_size );
    VertexBuffer[4].getTexCoord() = BoxE::Math::BVector2f ( 1.0f, 0.0f );

    VertexBuffer[5].getPosition() = BoxE::Math::BVector3f ( half_size, -half_size, -half_size ) ;
    VertexBuffer[5].getTexCoord() = BoxE::Math::BVector2f ( 0.0f, 0.0f ) ;

    VertexBuffer[6].getPosition() = BoxE::Math::BVector3f ( half_size, half_size, -half_size ) ;
    VertexBuffer[6].getTexCoord() = BoxE::Math::BVector2f ( 0.0f, 1.0f ) ;

    VertexBuffer[7].getPosition() = BoxE::Math::BVector3f ( -half_size, half_size, -half_size ) ;
    VertexBuffer[7].getTexCoord() = BoxE::Math::BVector2f ( 1.0f, 1.0f ) ;

    // Top
    VertexBuffer[8].getPosition() = BoxE::Math::BVector3f ( -half_size, half_size, half_size ) ;
    VertexBuffer[8].getTexCoord() = BoxE::Math::BVector2f ( 0.0f, 0.0f ) ;

    VertexBuffer[9].getPosition() = BoxE::Math::BVector3f ( half_size, half_size, half_size ) ;
    VertexBuffer[9].getTexCoord() = BoxE::Math::BVector2f ( 1.0f, 0.0f ) ;

    VertexBuffer[10].getPosition() = BoxE::Math::BVector3f ( half_size, half_size, -half_size ) ;
    VertexBuffer[10].getTexCoord() = BoxE::Math::BVector2f ( 1.0f, 1.0f ) ;

    VertexBuffer[11].getPosition() = BoxE::Math::BVector3f ( -half_size, half_size, -half_size ) ;
    VertexBuffer[11].getTexCoord() = BoxE::Math::BVector2f ( 0.0f, 1.0f ) ;

    // Bottom
    VertexBuffer[12].getPosition() = BoxE::Math::BVector3f ( -half_size, -half_size, half_size ) ;
    VertexBuffer[12].getTexCoord() = BoxE::Math::BVector2f ( 0.0f, 0.0f ) ;

    VertexBuffer[13].getPosition() = BoxE::Math::BVector3f ( half_size, -half_size, half_size ) ;
    VertexBuffer[13].getTexCoord() = BoxE::Math::BVector2f ( 1.0f, 0.0f );

    VertexBuffer[14].getPosition() = BoxE::Math::BVector3f ( half_size, -half_size, -half_size ) ;
    VertexBuffer[14].getTexCoord() = BoxE::Math::BVector2f ( 1.0f, 1.0f ) ;

    VertexBuffer[15].getPosition() = BoxE::Math::BVector3f ( -half_size, -half_size, -half_size ) ;
    VertexBuffer[15].getTexCoord() = BoxE::Math::BVector2f ( 0.0f, 1.0f ) ;

    // Left
    VertexBuffer[16].getPosition() = BoxE::Math::BVector3f ( half_size, -half_size, half_size ) ;
    VertexBuffer[16].getTexCoord() = BoxE::Math::BVector2f ( 0.0f, 0.0f ) ;

    VertexBuffer[17].getPosition() = BoxE::Math::BVector3f ( half_size, -half_size, -half_size ) ;
    VertexBuffer[17].getTexCoord() = BoxE::Math::BVector2f ( 1.0f, 0.0f ) ;

    VertexBuffer[18].getPosition() = BoxE::Math::BVector3f ( half_size, half_size, -half_size ) ;
    VertexBuffer[18].getTexCoord() = BoxE::Math::BVector2f ( 1.0f, 1.0f ) ;

    VertexBuffer[19].getPosition() = BoxE::Math::BVector3f ( half_size, half_size, half_size ) ;
    VertexBuffer[19].getTexCoord() = BoxE::Math::BVector2f ( 0.0f, 1.0f );
    // Right
    VertexBuffer[20].getPosition() = BoxE::Math::BVector3f ( -half_size, -half_size, half_size ) ;
    VertexBuffer[20].getTexCoord() = BoxE::Math::BVector2f ( 0.0f, 0.0f );

    VertexBuffer[21].getPosition() = BoxE::Math::BVector3f ( -half_size, -half_size, -half_size ) ;
    VertexBuffer[21].getTexCoord() = BoxE::Math::BVector2f ( 1.0f, 0.0f ) ;

    VertexBuffer[22].getPosition() = BoxE::Math::BVector3f ( -half_size, half_size, -half_size ) ;
    VertexBuffer[22].getTexCoord() = BoxE::Math::BVector2f ( 1.0f, 1.0f ) ;

    VertexBuffer[23].getPosition() = BoxE::Math::BVector3f ( -half_size, half_size, half_size ) ;
    VertexBuffer[23].getTexCoord() = BoxE::Math::BVector2f ( 0.0f, 1.0f ) ;

    VertexBuffer.setColor ( BoxE::Math::BVector4f ( 1.0f, 1.0f, 1.0f, 1.0f ) );
}

int BCubeMesh::getSize() const {
    return Size;
}

BackGenEngine::BAbstractComponent *BCubeMesh::duplicate() const {
    return new BCubeMesh ( getScene() );
}

extern "C" {
    BASE_MODULE_HEADER ( BackGenEngine::COMPONENT, "CubeMesh", "0.0.1", "Ondra Voves" );

    BackGenEngine::BAbstractComponent *createComponent ( BackGenEngine::BScene *pc_scene ) {
        return new BCubeMesh ( pc_scene );
    }
}
