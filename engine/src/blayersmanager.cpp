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


#include "../include/blayersmanager.h"
#include "../include/blogger.h"


namespace BackGenEngine {
    BLayersManager::BLayersManager ( BLogger *logger ) : Logger ( logger ) {
        if ( Logger ) {
            Logger->debug ( "Creating layers manager." );
        }

    }

    BLayersManager::~BLayersManager() {
        if ( Logger ) {
            Logger->debug ( "Destroing layers manager." );
        }

        blayer_type_hash_t::ConstIterator it = Layers.constBegin();
        while ( it != Layers.constEnd() ) {
            blayer_hash_t::ConstIterator it2 = ( *it )->constBegin();
            while ( it2 != ( *it )->constEnd() ) {
                delete ( *it2 );
                ++it2;
            }
            ++it;
        }
    }

    BLayersManager::blayer_type_hash_t &BLayersManager::layersTypeHash() {
        return Layers;
    }

    bool BLayersManager::containLayer ( const BoxE::Core::BAsciiString &name  ) const {
        blayer_type_hash_t::ConstIterator it = Layers.constBegin();
        while ( it != Layers.constEnd() ) {
            if ( ( *it )->contains ( name ) ) {
                return true;
            }
            ++it;
        }
        return false;
    }

    BLayer *BLayersManager::getLayer ( const BoxE::Core::BAsciiString &name ) const {
        blayer_type_hash_t::ConstIterator it = Layers.constBegin();
        while ( it != Layers.constEnd() ) {
            blayer_hash_t::ConstIterator it2 = ( *it )->constBegin();
            while ( it2 != ( *it )->constEnd() ) {
                if ( ( *it2 )->getName() == name ) {
                    return ( *it2 );
                }
                ++it2;
            }

            ++it;
        }
        return 0;
    }

    BLayer *BLayersManager::createLayer ( const BoxE::Core::BAsciiString &name, BLayer::ELayerType type ) {
        if ( containLayer ( name ) ) {
            return 0;
        }

        BLayer *new_layer =  new BLayer ( name, type, Logger );

        if ( insertLayer ( new_layer ) ) {
            return new_layer;
        } else {
            delete new_layer;
            return 0;
        }
    }

    bool BLayersManager::removeLayer ( BLayer *layer ) {
        if ( layer == 0 ) {
            return false;
        }

        blayer_type_hash_t::Iterator it = Layers.find ( layer->getLayerType() );
        blayer_hash_t::Iterator it2 = ( *it )->begin();
        while ( it2 != ( *it )->end() ) {
            if ( ( *it2 ) == layer ) {
                ( *it )->erase ( it2 ) != ( *it )->end();
                return true;
            }
            ++it2;
        }
        return false;
    }

    bool BLayersManager::removeLayer ( const BoxE::Core::BAsciiString &name ) {
        return removeLayer ( getLayer ( name ) );
    }

    BoxE::Core::BByteArray ELayerType2ByteArry ( BLayer::ELayerType type ) {
        switch ( type ) {
            case BLayer::NORMAL:
                return "NORMAL";

            case BLayer::TRANSPARENT:
                return "TRANSPARENT";

            case BLayer::GUI:
                return "GUI";
        }
    }

    BLayer::ELayerType ByteArry2ELayerType ( const  BoxE::Core::BByteArray &type ) {
        if ( type == "NORMAL" ) {
            return BLayer::NORMAL;
        } else if ( type == "GUI" ) {
            return BLayer::GUI;
        } else if ( type == "TRANSPARENT" ) {
            return BLayer::TRANSPARENT;
        }
    }

    BoxE::Core::BByteArray BLayersManager::toByteArray() {
        BoxE::Core::BByteArray str ( "layers_manager {\n"
                                     "%1"
                                     "}\n" );

        BoxE::Core::BByteArray layers_str;
        BoxE::Core::BByteArray layer_str;
        blayer_type_hash_t::ConstIterator it = Layers.constBegin();
        while ( it != Layers.constEnd() ) {
            blayer_hash_t::ConstIterator it2 = ( *it )->constBegin();
            while ( it2 != ( *it )->constEnd() ) {
                layer_str = "\tlayer %1 %2\n";
                layer_str.replace ( "%1", ( *it2 )->getName() );
                layer_str.replace ( "%2", ELayerType2ByteArry ( ( *it2 )->getLayerType() ) );
                layers_str.append ( layer_str );
                ++it2;
            }
            ++it;
        }

        str.replace ( "%1", layers_str );

        return str;
    }

    bool BLayersManager::fromByteArray ( const BoxE::Core::BByteArray &byte_array ) {
        BoxE::Core::BLinkedList<BoxE::Core::BByteArray> list = byte_array.split ( ' ' );

        int block_count = 0;
        BoxE::Core::BLinkedList<BoxE::Core::BByteArray>::ConstIterator it = list.constBegin();
        while ( it != list.constEnd() ) {
            if ( ( *it ) == "layers_manager" ) {
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

                    } else if ( ( *it ) == "layer" ) {
                        if ( ++it == list.constEnd() ) {
                            return false;
                        }

                        BoxE::Core::BByteArray name = ( *it );

                        if ( ++it == list.constEnd() ) {
                            return false;
                        }

                        BLayer::ELayerType type = ByteArry2ELayerType ( *it );

                        createLayer ( name, type );
                    }
                }
            } else {
                return false;
            }
        }
    }

    bool BLayersManager::insertLayer ( BLayer *layer ) {
        blayer_type_hash_t::Iterator it = Layers.find ( layer->getLayerType() );
        if ( it != Layers.end() ) {
            if ( ! ( *it )->contains ( layer->getName() ) ) {
                if ( ( *it )->insert ( layer->getName(), layer ) ) {
                    layer->onNameChanged().connect ( this, &BLayersManager::onLayerNameChaned );
                    layer->onLayerTypeChanged().connect ( this, &BLayersManager::onLayerTypeChaned );
                    return true;
                }
                return false;
            } else {
                return false;
            }
        } else {
            blayer_hash_t *l = new blayer_hash_t();
            if ( l->insert ( layer->getName(), layer ) ) {
                layer->onNameChanged().connect ( this, &BLayersManager::onLayerNameChaned );
                layer->onLayerTypeChanged().connect ( this, &BLayersManager::onLayerTypeChaned );
                Layers.insert ( layer->getLayerType(), l );
                return true;
            }
            return false;
        }

        return false;
    }

    void BLayersManager::onLayerTypeChaned ( BLayer *layer, BLayer::ELayerType new_type ) {
        blayer_type_hash_t::Iterator it1 = Layers.find ( layer->getLayerType() );

        if ( it1 == Layers.end() ) {
            return;
        }

        blayer_hash_t::Iterator it = ( *it1 )->begin();
        while ( it != ( *it1 )->end() ) {
            if ( ( *it ) == layer ) {
                ( *it1 )->erase ( it );

                layer->onLayerTypeChanged().disconnect ( this, &BLayersManager::onLayerTypeChaned );
                layer->onNameChanged().disconnect ( this, &BLayersManager::onLayerNameChaned );

                insertLayer ( layer );
                return;
            }
            it++;
        }
    }

    void BLayersManager::onLayerNameChaned ( BLayer *layer, BoxE::Core::BAsciiString new_name  ) {
        blayer_type_hash_t::Iterator it1 = Layers.find ( layer->getLayerType() );

        if ( it1 == Layers.end() ) {
            return;
        }

        blayer_hash_t::Iterator it = ( *it1 )->begin();
        while ( it != ( *it1 )->end() ) {
            if ( ( *it ) == layer ) {
                ( *it1 )->erase ( it );
                ( *it1 )->insert ( new_name, layer );
                return;
            }
            it++;
        }
    }

}