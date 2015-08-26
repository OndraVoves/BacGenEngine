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


#include "../include/bscene.h"

#include "../include/bobject.h"

namespace BackGenEngine {

    BScene::BScene ( BAbstractRenderer *pc_renderer, BLogger *logger ) : TagsManager ( logger ), LayersManager ( logger ), pcRenderer ( pc_renderer ) {
    }

    BScene::~BScene() {
    }

    BoxE::Core::BAsciiString BScene::getName() const {
        return Name;
    }

    void BScene::setName ( const BoxE::Core::BAsciiString &new_name ) {
        OnNameChanged.emitSignal ( this, new_name );
        Name = new_name;
    }

    void BScene::setActiveCameraObject ( BObject *pc_camera ) {
        pcActiveCameraObject = pc_camera;
    }

    BObject *BScene::getActiveCameraObject() {
        return pcActiveCameraObject;
    }

    BLayersManager &BScene::getLayersManager() {
        return LayersManager;
    }

    BTagsManager &BScene::getTagsManager() {
        return TagsManager;
    }

    BAbstractRenderer *BScene::getRenderer() {
        return pcRenderer;
    }

    BoxE::Core::BByteArray BScene::toByteArray() {
        BoxE::Core::BByteArray str ( "scene {\n"
                                     "\tname %1\n"
                                     "%2"
                                     "%3"
                                     "\tobjects {\n"
                                     "%4"
                                     "\t\thiearchy {\n"
                                     "%5"
                                     "\t\t}\n"
                                     "\t}\n"
                                     "}\n" );
        str.replace ( "%1", Name );
        str.replace ( "%2", LayersManager.toByteArray().replace ( "\t", BoxE::Core::BByteArray ( "\t\t" ) )
                      .replace ( "layers_manager", BoxE::Core::BByteArray ( "\tlayers_manager" ) )
                      .replace ( "}", BoxE::Core::BByteArray ( "\t}" ) ) );

        str.replace ( "%3", TagsManager.toByteArray().replace ( "\t", BoxE::Core::BByteArray ( "\t\t" ) )
                      .replace ( "tags_manager", BoxE::Core::BByteArray ( "\ttags_manager" ) )
                      .replace ( "}", BoxE::Core::BByteArray ( "\t}" ) ) );

        BoxE::Core::BByteArray objects;

        BTag::bobject_hash_t::ConstIterator it = TagsManager.rootTag().constBegin();
        while ( it != TagsManager.rootTag().constEnd() ) {
            objects.append ( ( *it )->toByteArray() );
            ++it;
        }

        str.replace ( "%4", objects );

        BoxE::Core::BByteArray hiearchy;
        BTag::bobject_hash_t::ConstIterator it2 = TagsManager.rootTag().constBegin();
        while ( it2 != TagsManager.rootTag().constEnd() ) {
            if ( ( *it2 )->getParent() ) {
                BoxE::Core::BByteArray obj ( "\t\tset_parent %1 %2\n" );
                obj.replace ( "%1", ( *it2 )->getName() );
                obj.replace ( "%2", ( *it2 )->getParent()->getName() );
                hiearchy.append ( obj );
            }

            ++it2;
        }

        str.replace ( "%5", hiearchy );

        return str;
    }

    bool BScene::fromByteArray ( const BoxE::Core::BByteArray &byte_array, BAbstractModuleSystem *pc_modules_system,  BAssetManager *pc_asset_manager ) {
        BoxE::Core::BByteArray array;
        array.reserve ( byte_array.size() );

        const char *ch = byte_array.constData();
        while ( ( *ch ) != '\0' ) {
            if ( ( *ch ) == '\t' ) {
                ++ch;
                continue;
            } else if ( ( *ch ) == '\n' ) {
                array.append ( " " );
            } else {
                array.append ( ( *ch ) );
            }

            ++ch;
        }
        array.squeeze();

        BoxE::Core::BLinkedList<BoxE::Core::BByteArray> list = array.split ( ' ' );

        int block_count = 0;
        BoxE::Core::BLinkedList<BoxE::Core::BByteArray>::ConstIterator it = list.constBegin();
        while ( it != list.constEnd() ) {
            if ( ( *it ) == "scene" ) {
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

                    } else if ( ( *it ) == "name" ) {

                        if ( ++it == list.constEnd() ) {
                            return false;
                        }

                        BoxE::Core::BByteArray name = ( *it );

                        setName ( name );
                    } else if ( ( *it ) == "layers_manager" ) {
                        BoxE::Core::BByteArray layers_array;
                        while ( ! ( ( *it ) == "}" ) ) {
                            layers_array.append ( *it );
                            layers_array.append ( " " );
                            ++it;
                        }
                        layers_array.append ( "}" );
                        LayersManager.fromByteArray ( layers_array );

                    } else if ( ( *it ) == "tags_manager" ) {
                        BoxE::Core::BByteArray tags_array;
                        while ( ! ( ( *it ) == "}" ) ) {
                            tags_array.append ( *it );
                            tags_array.append ( " " );

                            ++it;
                        }
                        tags_array.append ( "}" );
                        TagsManager.fromByteArray ( tags_array );

                    } else if ( ( *it ) == "tags_manager" ) {
                        BoxE::Core::BByteArray tags_array;
                        while ( ! ( ( *it ) == "}" ) ) {
                            tags_array.append ( *it );
                            tags_array.append ( " " );

                            ++it;
                        }
                        tags_array.append ( "}" );
                        TagsManager.fromByteArray ( tags_array );

                    } else if ( ( *it ) == "objects" ) {
                        if ( ++it == list.constEnd() ) {
                            return false;
                        }

                        int objects_block = 0;
                        if ( ( *it ) == "{" ) {
                            objects_block++;
                        } else {
                            return false;
                        }

                        while ( objects_block != 0 ) {
                            if ( ++it == list.constEnd() ) {
                                return false;
                            }

                            if ( ( *it ) == "}" ) {
                                objects_block--;

                            } else if ( ( *it ) == "object" ) {
                                int object_block = -1;
                                BoxE::Core::BByteArray object_array;
                                while ( object_block != 0 ) {
                                    if ( ( *it ) == "{" ) {
                                        if ( object_block == -1 ) {
                                            object_block = 1;
                                        } else {
                                            object_block++;
                                        }

                                    } else if ( ( *it ) == "}" ) {
                                        object_block--;
                                    }

                                    object_array.append ( *it );
                                    object_array.append ( " " );

                                    ++it;
                                }

                                //object_array.append ( "}" );

                                BObject *pc_new_object = new BObject ( "", 0 );
                                pc_new_object->fromByteArray ( object_array, &LayersManager, &TagsManager, pc_modules_system, this, pc_asset_manager );

                                TagsManager.rootTag().insertObject ( pc_new_object );
                                --it;

                            } else if ( ( *it ) == "hiearchy" ) {
                                if ( ++it == list.constEnd() ) {
                                    return false;
                                }

                                int hiearchy_block = 0;

                                if ( ( *it ) == "{" ) {
                                    hiearchy_block = 1;
                                } else {
                                    return false;
                                }

                                while ( hiearchy_block != 0 ) {
                                    if ( ++it == list.constEnd() ) {
                                        return false;
                                    }

                                    if ( ( *it ) == "}" ) {
                                        hiearchy_block--;

                                    } else if ( ( *it ) == "set_parent" ) {
                                        if ( ++it == list.constEnd() ) {
                                            return false;
                                        }

                                        BoxE::Core::BByteArray object_name = ( *it );
                                        BObject *pc_object = TagsManager.rootTag().getObject ( object_name );

                                        if ( ++it == list.constEnd() ) {
                                            return false;
                                        }

                                        BoxE::Core::BByteArray parent_object_name = ( *it );
                                        BObject *pc_parent_object = TagsManager.rootTag().getObject ( parent_object_name );

                                        pc_object->setParent ( pc_parent_object );
                                    }
                                }
                            }
                        }
                    }

                }

            } else {
                return false;
            }
        }

    }

    BoxE::Core::BSignal2< BScene *, BoxE::Core::BAsciiString >& BScene::onNameChanged() {
        return OnNameChanged;
    }


}
