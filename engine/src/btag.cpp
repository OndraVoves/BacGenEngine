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


#include "../include/btag.h"
#include "../include/bobject.h"

namespace BackGenEngine {

    BTag::BTag ( const BoxE::Core::BAsciiString &name ) : Name ( name ) {
    }

    BTag::~BTag() {
        bobject_hash_t::Iterator it = ObjectsHash.begin();
        while ( it != ObjectsHash.end() ) {
            ( *it )->removeTag ( this );
            ( *it )->onNameChanged().disconnect ( this, &BTag::objectNameChanged );
            it = ObjectsHash.erase ( it );
        }
    }

    BoxE::Core::BAsciiString BTag::getName() const {
        return Name;
    }

    void BTag::setName ( const BoxE::Core::BAsciiString &new_name ) {
        OnNameChanged.emitSignal ( this, new_name );
        Name = new_name;
    }


    BTag::bobject_hash_t::ConstIterator BTag::constBegin() const {
        return ObjectsHash.constBegin();
    }

    BTag::bobject_hash_t::ConstIterator BTag::constEnd() const {
        return ObjectsHash.constEnd();
    }

    bool BTag::insertObject ( BObject *object ) {
        if ( object == 0 ) {
            return false;
        }

        if ( containObject ( object ) ) {
            return false;
        }

        if ( ObjectsHash.insert ( object->getName(), object ) ) {
            object->onNameChanged().connect ( this, &BTag::objectNameChanged );
            object->addTag ( this );
            return true;
        }

        return false;
    }

    bool BTag::removeObject ( BObject *object ) {
        bobject_hash_t::Iterator it = ObjectsHash.begin();
        while ( it != ObjectsHash.end() ) {
            if ( ( *it ) == object ) {
                ObjectsHash.erase ( it );
                object->removeTag ( this );
                object->onNameChanged().disconnect ( this, &BTag::objectNameChanged );
                return true;
            }
            it++;
        }
        return false;
    }

    bool BTag::removeObject ( const BoxE::Core::BAsciiString &name ) {
        bobject_hash_t::Iterator it = ObjectsHash.begin();
        while ( it != ObjectsHash.end() ) {
            if ( ( *it )->getName() == name ) {
                ObjectsHash.erase ( it );
                ( *it )->onNameChanged().disconnect ( this, &BTag::objectNameChanged );
                ( *it )->removeTag ( this );
                return true;
            }
            it++;
        }

        return false;
    }

    bool BTag::containObject ( BObject *object ) const {
        return ObjectsHash.contains ( object->getName() );
    }

    bool BTag::containObject ( const BoxE::Core::BAsciiString &name ) const {
        return ObjectsHash.contains ( name );
    }

    BObject *BTag::getObject ( const BoxE::Core::BAsciiString &name ) {
        bobject_hash_t::Iterator it = ObjectsHash.find ( name );
        if ( it == ObjectsHash.end() ) {
            return 0;
        } else {
            return ( *it );
        }
    }

    BoxE::Core::BSignal2< BTag *, BoxE::Core::BAsciiString >& BTag::onNameChanged() {
        return OnNameChanged;
    }

    void BTag::objectNameChanged ( BObject *obj, BoxE::Core::BAsciiString new_name ) {
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



}