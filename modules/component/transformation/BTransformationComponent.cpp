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

#include "./BTransformationComponent.h"

BGE_RTTI_IMPLEMENTATION ( BackGenEngine, BTransformationComponent, BAbstractComponent );

BTransformationComponent::BTransformationComponent ( BackGenEngine::BScene *pc_scene ) : BAbstractComponent ( pc_scene ), Scale ( 1.0f, 1.0f, 1.0f ) {
}

BTransformationComponent::~BTransformationComponent( ) {
}

BoxE::Math::BMatrix4x4f BTransformationComponent::getObjectSpaceMatrix() const {
    BoxE::Math::BMatrix4x4f obj_spc_matrix ( BoxE::Math::BMatrix4x4f::IDENTITY );

    obj_spc_matrix.translate ( Position );

    obj_spc_matrix.rotateX ( Rotation.x() );
    obj_spc_matrix.rotateY ( Rotation.y() );
    obj_spc_matrix.rotateZ ( Rotation.z() );

    obj_spc_matrix.scale ( Scale );

    return obj_spc_matrix;
}


BackGenEngine::BAbstractComponent *BTransformationComponent::duplicate() const {
    BTransformationComponent *pc_duplicate = new BTransformationComponent ( getScene() );

    pc_duplicate->Position = Position;
    pc_duplicate->Rotation = Rotation;
    pc_duplicate->Scale = Scale;

    return pc_duplicate;
}

BoxE::Core::BByteArray BTransformationComponent::toByteArray() {
    BoxE::Core::BByteArray str ( "\tposition %1\n"
                                 "\trotation %2\n"
                                 "\tscale %3\n" );
    char tmp_buffer[128];

    // Position.
    sprintf ( tmp_buffer, "%f %f %f", Position.x(), Position.y(), Position.z() );
    str.replace ( "%1", BoxE::Core::BByteArray ( tmp_buffer ) );

    // Rotation.
    sprintf ( tmp_buffer, "%f %f %f", Rotation.x(), Rotation.y(), Rotation.z() );
    str.replace ( "%2", BoxE::Core::BByteArray ( tmp_buffer ) );

    // Scale.
    sprintf ( tmp_buffer, "%f %f %f", Scale.x(), Scale.y(), Scale.z() );
    str.replace ( "%3", BoxE::Core::BByteArray ( tmp_buffer ) );

    return str;
}

bool BTransformationComponent::fromByteArray ( const BoxE::Core::BByteArray &byte_array, BackGenEngine::BAssetManager *pc_asset_manager ) {
    BoxE::Core::BLinkedList<BoxE::Core::BByteArray> list = byte_array.split ( ' ' );

    int block_count = 0;
    BoxE::Core::BLinkedList<BoxE::Core::BByteArray>::ConstIterator it = list.constBegin();
    while ( it != list.constEnd() ) {

        if ( ( *it ) == "Transformation" ) {
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

                } else if ( ( *it ) == "position" ) {
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

                    if ( ++it == list.constEnd() ) {
                        return false;
                    }

                    numbers.append ( *it );
                    numbers.append ( " " );


                    float x, y, z;

                    sscanf ( numbers.constData(), "%f %f %f", &x, &y, &z );

                    Position.setXYZ ( x, y, z );

                } else if ( ( *it ) == "rotation" ) {
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

                    if ( ++it == list.constEnd() ) {
                        return false;
                    }

                    numbers.append ( *it );
                    numbers.append ( " " );


                    float x, y, z;

                    sscanf ( numbers.constData(), "%f %f %f", &x, &y, &z );

                    Rotation.setXYZ ( x, y, z );
                } else if ( ( *it ) == "scale" ) {
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

                    if ( ++it == list.constEnd() ) {
                        return false;
                    }

                    numbers.append ( *it );
                    numbers.append ( " " );


                    float x, y, z;

                    sscanf ( numbers.constData(), "%f %f %f", &x, &y, &z );

                    Scale.setXYZ ( x, y, z );
                }
            }
        }

        ++it;
    }
}

extern "C" {
    BASE_MODULE_HEADER ( BackGenEngine::COMPONENT, "Transformation", "0.0.1", "Ondra Voves" );

    BackGenEngine::BAbstractComponent *createComponent ( BackGenEngine::BScene *pc_scene ) {
        return new BTransformationComponent ( pc_scene );
    }
}
