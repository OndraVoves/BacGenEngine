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


#include "../include/blayer.h"
#include "../include/bobject.h"
#include "../include/blogger.h"

namespace BackGenEngine {

    BLayer::BLayer ( const BoxE::Core::BAsciiString &new_name, ELayerType layer_type,  BLogger *pc_logger ) : pcLogger ( pc_logger ),  Name ( new_name ), LayerType ( layer_type ) {
        BGE_LOGGER_DEBUG ( pcLogger, "BLayer", "BLayer", BoxE::Core::BAsciiString ( "Creating layer \"%1\"" ).replace ( "%1", Name ) );
    }

    BLayer::~BLayer() {
        BGE_LOGGER_DEBUG ( pcLogger, "BLayer", "~BLayer", BoxE::Core::BAsciiString ( "Destroing layer \"%1\"" ).replace ( "%1", Name ) );

        bobject_hash_t::Iterator it = ObjectsHash.begin();
        while ( it != ObjectsHash.end() ) {
            ( *it )->onNameChanged().disconnect ( this, &BLayer::objectNameChanged );
            ( *it )->setLayer ( 0 );
            it = ObjectsHash.erase ( it );
        }
    }

    BoxE::Core::BAsciiString BLayer::getName() const {
        return Name;
    }


    BLayer::ELayerType BLayer::getLayerType() const {
        return LayerType;
    }


    void BLayer::setLayerType ( BLayer::ELayerType layer_type ) {
        OnLayerTypeChanged.emitSignal ( this, layer_type );
        LayerType = layer_type;
    }

    void BLayer::setName ( const BoxE::Core::BAsciiString &new_name ) {
        OnNameChanged.emitSignal ( this, new_name );
        Name = new_name;
    }

    BLayer::bobject_hash_t::ConstIterator BLayer::constBegin() const {
        return ObjectsHash.constBegin();
    }

    BLayer::bobject_hash_t::ConstIterator BLayer::constEnd() const {
        return ObjectsHash.constEnd();
    }

    bool BLayer::insertObject ( BObject *object ) {
        if ( object == 0 ) {
            return false;
        }

        if ( containObject ( object ) ) {
            return false;
        }

        if ( ObjectsHash.insert ( object->getName(), object ) ) {
            object->onNameChanged().connect ( this, &BLayer::objectNameChanged );

            if ( object->layer() == 0 ) {
                object->setLayer ( this );
            } else {
                object->layer()->removeObject ( object );
                object->setLayer ( this );
            }

            return true;
        }

        return false;
    }

    bool BLayer::removeObject ( BObject *object ) {
        bobject_hash_t::Iterator it = ObjectsHash.begin();
        while ( it != ObjectsHash.end() ) {
            if ( ( *it ) == object ) {
                ObjectsHash.erase ( it );
                object->setLayer ( 0 );
                object->onNameChanged().disconnect ( this, &BLayer::objectNameChanged );
                return true;
            }
            it++;
        }
        return false;
    }

    bool BLayer::removeObject ( const BoxE::Core::BAsciiString &name ) {
        bobject_hash_t::Iterator it = ObjectsHash.begin();
        while ( it != ObjectsHash.end() ) {
            if ( ( *it )->getName() == name ) {
                ObjectsHash.erase ( it );
                ( *it )->onNameChanged().disconnect ( this, &BLayer::objectNameChanged );
                ( *it )->setLayer ( 0 );
                return true;
            }
            it++;
        }

        return false;
    }

    bool BLayer::containObject ( BObject *object ) const {
        return ObjectsHash.contains ( object->getName() );
    }

    bool BLayer::containObject ( const BoxE::Core::BAsciiString &name ) const {
        return ObjectsHash.contains ( name );
    }

    BoxE::Core::BSignal2< BLayer *, BoxE::Core::BAsciiString >& BLayer::onNameChanged() {
        return OnNameChanged;
    }

    BoxE::Core::BSignal2< BLayer *, BLayer::ELayerType >& BLayer::onLayerTypeChanged() {
        return OnLayerTypeChanged;
    }

    void BLayer::objectNameChanged ( BObject *obj, BoxE::Core::BAsciiString new_name ) {
        bobject_hash_t::Iterator it = ObjectsHash.begin();
        while ( it != ObjectsHash.end() ) {
            if ( ( *it ) == obj ) {
                ObjectsHash.erase ( it );
                ObjectsHash.insert ( new_name, obj );
                return;
            }
            it++;
        }
    }

    long bCalcHash ( BLayer::ELayerType type ) {
        return long ( type );
    }

}
