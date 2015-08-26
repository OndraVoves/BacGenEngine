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


#include "../include/bobject.h"

#include "../include/babstractcomponent.h"
#include "../include/btag.h"
#include "../include/btagsmanager.h"
#include "../include/blayer.h"
#include "../include/blayersmanager.h"
#include "../include/babstractmodulesystem.h"

namespace BackGenEngine {

    BObject::BObject() : pParent ( 0 ), pLayer ( 0 ) {
    }

    BObject::BObject ( const BoxE::Core::BAsciiString &new_name, BObject *parent ) : Name ( new_name ), pParent ( 0 ), pLayer ( 0 ) {
        setParent ( parent );
    }

    BObject::~BObject() {
        setParent ( 0 );

        if ( pLayer ) {
            pLayer->removeObject ( this );
        }

        setLayer ( 0 );

        btags_hash_t::Iterator it = Tags.begin();
        while ( it != Tags.end() ) {
            ( *it )->removeObject ( this );
            ++it;
        }

        objects_list_t::ConstIterator obj_it = ChildObjects.constBegin();
        BObject *pc_actual_duplicate = 0;
        while ( obj_it != ChildObjects.constEnd() ) {
            delete ( *obj_it );
            ++obj_it;
        }
    }

    BoxE::Core::BAsciiString BObject::getName( ) const {
        return Name;
    }


    void BObject::setName ( const BoxE::Core::BAsciiString &new_name ) {
        OnNameChanged.emitSignal ( this, new_name );
        Name = new_name;
    }


    BObject *BObject::getParent( ) const {
        return pParent;
    }

    void BObject::setParent ( BObject *p ) {
        if ( pParent != 0 ) {
            pParent->removeChild ( this );
        }

        if ( p != 0 ) {
            p->ChildObjects.append ( this );
        }

        pParent = p;
    }

    // Objects.
    const BObject::objects_list_t &BObject::getObjectsList() const {
        return ChildObjects;
    }

    // COmponents.
    const BObject::component_vector_t &BObject::getComponentVector() const {
        return Components;
    }

    bool BObject::insertComponent ( BAbstractComponent *component ) {
        if ( component == 0 ) {
            return false;
        }

        component_vector_t::Iterator it = Components.begin();
        while ( it != Components.end() ) {
            if ( ( *it )->getName() == component->getName() ) {
                return false;
            }
            ++it;
        }

        Components.append ( component );

        component->pOwnerObject = this;

        return true;
    }

    bool BObject::removeComponent ( BAbstractComponent *component ) {
        if ( component == 0 ) {
            return false;
        }

        component_vector_t::Iterator it = Components.begin();
        while ( it != Components.end() ) {
            if ( ( *it ) == component ) {
                Components.remove ( it );
                component->pOwnerObject = 0;
                return true;
            }
            it++;
        }

        return false;
    }


    BAbstractComponent *BObject::getComponentByName ( const BoxE::Core::BAsciiString &name ) {
        component_vector_t::Iterator it = Components.begin();
        while ( it != Components.end() ) {
            if ( ( *it )->getName() == name ) {
                return *it;
            }
            it++;
        }

        return 0;
    }

    void BObject::setLayer ( BLayer *layer ) {
        pLayer = layer;
    }

    bool BObject::isInTag ( const BoxE::Core::BAsciiString &name ) {
        return Tags.contains ( name );
    }

    BLayer *BObject::layer() const {
        return pLayer;
    }

    const BObject::btags_hash_t &BObject::tagsHash() const {
        return Tags;
    }

    BoxE::Core::BByteArray BObject::toByteArray() {
        BoxE::Core::BByteArray str ( "object {\n"
                                     "\tname %1\n"
                                     "%2"
                                     "%3"
                                     "%4"
                                     "}\n" );
        str.replace ( "%1", Name );

        if ( pLayer ) {
            str.replace ( "%2", BoxE::Core::BByteArray ( "\tlayer %2\n" ) );
            str.replace ( "%2", pLayer->getName() );
        } else {
            str.replace ( "%2", BoxE::Core::BByteArray() );
        }

        BoxE::Core::BByteArray tags;
        BoxE::Core::BByteArray tag;
        btags_hash_t::ConstIterator it = Tags.constBegin();
        while ( it != Tags.constEnd() ) {
            if ( ( *it )->getName().startsWith ( "_" ) ) {
                ++it;
                continue;
            }

            tag = "\ttag %1\n";
            tag.replace ( "%1", ( *it )->getName() );
            tags.append ( tag );
            ++it;
        }

        str.replace ( "%3", tags );

        BoxE::Core::BByteArray components;
        BoxE::Core::BByteArray component;
        component_vector_t::ConstIterator comp_it = Components.constBegin();
        while ( comp_it != Components.constEnd() ) {
            component = "component %1 {\n"
                        "%2"
                        "}\n";

            component.replace ( "%1", ( *comp_it )->getName() );
            component.replace ( "%2", ( *comp_it )->toByteArray() );

            components.append ( component );
            ++comp_it;
        }


        str.replace ( "%4", components );

        return str;
    }

    bool BObject::fromByteArray ( const BoxE::Core::BByteArray &byte_array,  BLayersManager *pc_layers_manager, BTagsManager *pc_tags_manager, BAbstractModuleSystem *pc_modules_system, BScene *pc_scene, BAssetManager *pc_asset_manager  ) {
        BoxE::Core::BLinkedList<BoxE::Core::BByteArray> list = byte_array.split ( ' ' );

        int block_count = 0;
        BoxE::Core::BLinkedList<BoxE::Core::BByteArray>::ConstIterator it = list.constBegin();
        while ( it != list.constEnd() ) {
            if ( ( *it ) == "object" ) {
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

                        BoxE::Core::BByteArray name ( *it );

                        setName ( name );

                    } else if ( ( *it ) == "layer" ) {
                        if ( ++it == list.constEnd() ) {
                            return false;
                        }

                        BoxE::Core::BByteArray name ( *it );

                        BLayer *pc_layer =  pc_layers_manager->getLayer ( name );
                        if ( pc_layer ) {
                            pc_layer->insertObject ( this );
                        }

                    } else if ( ( *it ) == "component" ) {
                        if ( ++it == list.constEnd() ) {
                            return false;
                        }

                        BoxE::Core::BByteArray type_name ( *it );

                        BAbstractComponent *pc_new_component = pc_modules_system->createComponent ( type_name, pc_scene );

                        int component_block = -1;
                        BoxE::Core::BByteArray component_array;
                        while ( component_block != 0 ) {
                            if ( ( *it ) == "{" ) {
                                if ( component_block == -1 ) {
                                    component_block = 1;
                                } else {
                                    component_block++;
                                }

                            } else if ( ( *it ) == "}" ) {
                                component_block--;
                            }

                            component_array.append ( *it );
                            component_array.append ( " " );

                            ++it;
                        }

                        if ( pc_new_component ) {
                            pc_new_component->fromByteArray ( component_array, pc_asset_manager );
                            insertComponent ( pc_new_component );
                        }
                        --it;
                    }
                }
            } else {
                return false;
            }
        }
    }

    BObject *BObject::duplicate() {
        BoxE::Core::BAsciiString new_name ( "%1_dupl%2" );
        new_name.replace ( "%1", Name );
        new_name.replace ( "%2", BoxE::Core::BAsciiString::number ( rand() ) );

        BObject *pc_duplicate = new BObject ( new_name, 0 );

        //Components;
        component_vector_t::ConstIterator it = Components.constBegin();
        while ( it != Components.constEnd() ) {
            pc_duplicate->insertComponent ( ( *it )->duplicate() );
            ++it;
        }

        // Layer.
        pLayer->insertObject ( pc_duplicate );

        objects_list_t::ConstIterator obj_it = ChildObjects.constBegin();
        BObject *pc_actual_duplicate = 0;
        while ( obj_it != ChildObjects.constEnd() ) {
            pc_actual_duplicate = ( *obj_it )->duplicate();
            pc_actual_duplicate->setParent ( pc_duplicate );

            ++obj_it;
        }

        // Tags.
        btags_hash_t::ConstIterator tag_it = Tags.constBegin();
        while ( tag_it != tagsHash().constEnd() ) {
            ( *tag_it )->insertObject ( pc_duplicate );
            ++tag_it;
        }

        return pc_duplicate;
    }

    BoxE::Core::BSignal2< BObject *, BoxE::Core::BAsciiString >& BObject::onNameChanged() {
        return OnNameChanged;
    }

    void BObject::removeChild ( BObject *obj ) {
        objects_list_t::Iterator it = ChildObjects.begin();
        while ( it != ChildObjects.end() ) {
            if ( ( *it )  == obj ) {
                ChildObjects.erase ( it );
            }
            it++;
        }
    }

    void BObject::addTag ( BTag *tag ) {
        if ( tag == 0 ) {
            return;
        }

        if ( Tags.contains ( tag->getName() ) ) {
            return;
        }

        tag->onNameChanged().connect ( this, &BObject::tagNameChanged );

        Tags.insert ( tag->getName(), tag );
    }

    void BObject::removeTag ( BTag *tag ) {
        if ( tag == 0 ) {
            return;
        }

        if ( !Tags.contains ( tag->getName() ) ) {
            return;
        }

        tag->onNameChanged().disconnect ( this, &BObject::tagNameChanged );

        Tags.erase ( Tags.find ( tag->getName() ) );
    }

    void BObject::tagNameChanged ( BTag *tag, BoxE::Core::BAsciiString new_name ) {
        btags_hash_t::Iterator it = Tags.begin();
        while ( it != Tags.end() ) {
            if ( ( *it ) == tag ) {
                Tags.erase ( it );
                Tags.insert ( new_name, tag );
                return;
            }
            it++;
        }
    }

}
