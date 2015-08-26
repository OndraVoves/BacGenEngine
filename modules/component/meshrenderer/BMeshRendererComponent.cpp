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

#include "./BMeshRendererComponent.h"

#include <GL/glew.h>

#include <cstdio>

#include <BackGenEngine/bobject.h>
#include <BackGenEngine/bscene.h>
#include <BackGenEngine/babstractrenderer.h>
#include <BackGenEngine/bassetmanager.h>

#include "../transformation/BTransformationComponent.h"
#include "../abstractmesh/BAbstractMesh.h"
#include "../../asset/material/BMaterialAsset.h"

BGE_RTTI_IMPLEMENTATION ( BackGenEngine, BMeshRendererComponent, BackGenEngine::BRenderableComponent );

BMeshRendererComponent::BMeshRendererComponent (  BackGenEngine::BScene *pc_scene )
    : BRenderableComponent ( pc_scene ), pcMaterialAsset ( 0 ), Tiling ( 1.0f, 1.0f ) {
    TextureMatrix.setToIdentity();
}

BMeshRendererComponent::~BMeshRendererComponent( ) {
}

void BMeshRendererComponent::setMaterialAsset ( BMaterialAsset *pc_asset ) {
    pcMaterialAsset = pc_asset;
}

BMaterialAsset *BMeshRendererComponent::getMaterialAsset() {
    return pcMaterialAsset;
}

void BMeshRendererComponent::render() {
    BTransformationComponent *pc_transform = getOwnerObject()->getComponent<BTransformationComponent>();
    BAbstractMesh *pc_mesh = getOwnerObject()->getComponent<BAbstractMesh>();

    int *indexb = pc_mesh->getIndexBuffer();
    BackGenEngine::BVertexBuffer *pc_vertex_buffer = pc_mesh->getVertexBuffer();

    glColor3f ( 1.0f, 1.0f, 1.0f );
    getScene()->getRenderer()->pushTextureMatrix ( 0 );
    getScene()->getRenderer()->pushTextureMatrix ( 1 );
    getScene()->getRenderer()->pushTextureMatrix ( 2 );
    getScene()->getRenderer()->pushTextureMatrix ( 3 );

    getScene()->getRenderer()->setTextureMatrix ( 0, TextureMatrix );
    getScene()->getRenderer()->setTextureMatrix ( 1, TextureMatrix );
    getScene()->getRenderer()->setTextureMatrix ( 2, TextureMatrix );
    getScene()->getRenderer()->setTextureMatrix ( 3, TextureMatrix );

    getScene()->getRenderer()->pushMatrix ( BackGenEngine::BAbstractRenderer::MT_WORLD );
    getScene()->getRenderer()->multMatrix ( BackGenEngine::BAbstractRenderer::MT_WORLD, pc_transform->getObjectSpaceMatrix() );
    if ( pcMaterialAsset ) {
        pcMaterialAsset->use();
        pcMaterialAsset->begin();
        getScene()->getRenderer()->renderVB ( BackGenEngine::BAbstractRenderer::PT_TRIANGLES,  *pc_vertex_buffer, pc_mesh->getIndexBuffer(), 12 );
        pcMaterialAsset->end();
        pcMaterialAsset->unuse();
    } else {
        getScene()->getRenderer()->renderVB ( BackGenEngine::BAbstractRenderer::PT_TRIANGLES,  *pc_vertex_buffer, pc_mesh->getIndexBuffer(), 12 );
    }

    getScene()->getRenderer()->popTextureMatrix ( 0 );
    getScene()->getRenderer()->popTextureMatrix ( 1 );
    getScene()->getRenderer()->popTextureMatrix ( 2 );
    getScene()->getRenderer()->popTextureMatrix ( 3 );

    getScene()->getRenderer()->popMatrix ( BackGenEngine::BAbstractRenderer::MT_WORLD ) ;
}

void BMeshRendererComponent::setTiling ( const BoxE::Math::BVector2f &tiling ) {
    Tiling = tiling;
    generateTextureMatrix();
}

BoxE::Math::BVector2f BMeshRendererComponent::getTiling( ) const {
    return Tiling;
}

BackGenEngine::BAbstractComponent *BMeshRendererComponent::duplicate() const {
    return new BMeshRendererComponent ( getScene() );
}

BoxE::Core::BByteArray BMeshRendererComponent::toByteArray() {
    if ( pcMaterialAsset ) {
        BoxE::Core::BByteArray str ( "\tmaterial %1\n"
                                     "\ttiling %2\n"
                                   );

        str.replace ( "%1", pcMaterialAsset->getName() );

        char buffer[256];
        sprintf ( buffer, "%f %f", Tiling.x(), Tiling.y() );

        str.replace ( "%2", BoxE::Core::BByteArray ( buffer ) );

        return str;
    }

    return BoxE::Core::BByteArray();
}

bool BMeshRendererComponent::fromByteArray ( const BoxE::Core::BByteArray &byte_array, BackGenEngine::BAssetManager *pc_asset_manager ) {
    BoxE::Core::BLinkedList<BoxE::Core::BByteArray> list = byte_array.split ( ' ' );

    int block_count = 0;
    BoxE::Core::BLinkedList<BoxE::Core::BByteArray>::ConstIterator it = list.constBegin();
    while ( it != list.constEnd() ) {

        if ( ( *it ) == "MeshRenderer" ) {
            if ( ++it == list.constEnd() ) {
                return false;
            }

            if ( ( *it ) == "{" ) {
                block_count = 1;
            } else {
                return false;
            }

            while ( block_count != 0 ) {
                if ( ++it == list.constEnd() ) {
                    return false;
                }

                if ( ( *it ) == "}" ) {
                    block_count--;

                } else if ( ( *it ) == "material" ) {
                    if ( ++it == list.constEnd() ) {
                        return false;
                    }

                    BoxE::Core::BByteArray name = *it;

                    // TODO RTTI
                    BMaterialAsset *pc_asset = ( BMaterialAsset * ) pc_asset_manager->getAsset ( name );
                    setMaterialAsset ( pc_asset );

                } else if ( ( *it ) == "tiling" ) {
                    if ( ++it == list.constEnd() ) {
                        return false;
                    }

                    BoxE::Core::BByteArray numbers;

                    numbers.append ( *it );
                    numbers.append ( " " );

                    if ( ++it == list.constEnd() ) {
                        return false;
                    }

                    numbers.append ( *it );
                    numbers.append ( " " );

                    float x = 0.0f;
                    float y = 0.0f;

                    sscanf ( numbers.constData(), "%f %f", &x, &y );


                    Tiling.x ( x );
                    Tiling.y ( y );
                    generateTextureMatrix();
                }
            }
        }

        ++it;
    }
}

void BMeshRendererComponent::generateTextureMatrix() {
    TextureMatrix.setToIdentity();
    TextureMatrix.scale ( BoxE::Math::BVector3f ( Tiling.x(), Tiling.y(), 1.0f ) );
}


extern "C" {
    BASE_MODULE_HEADER ( BackGenEngine::COMPONENT, "MeshRenderer", "0.0.1", "Ondra Voves" );

    BackGenEngine::BAbstractComponent *createComponent ( BackGenEngine::BScene *pc_scene ) {
        return new BMeshRendererComponent ( pc_scene );
    }
}
