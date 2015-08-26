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


#include "../include/bactionmanager.h"
#include "../include/babstractaction.h"

namespace BackGenEngine {

    BActionManager::BActionManager() {
    }

    BActionManager::~BActionManager() {
    }

    BAbstractAction *BActionManager::find ( const BoxE::Core::BAsciiString &name ) {
        if ( Actions.isEmpty() ) {
            return 0;
        }

        return Actions.find ( name ).value();
    }


    bool BActionManager::contains ( const BoxE::Core::BAsciiString &name ) const {
        return Actions.contains ( name );
    }

    bool BActionManager::insert ( BAbstractAction *action ) {
        if ( action == 0 ) {
            return false;
        }

        if ( contains ( action->getName() ) ) {
            return false;
        }

        if ( Actions.insert ( action->getName(), action ) ) {
            action->onNameChanged().connect ( this, &BActionManager::actionNameChanged );
            return true;

        } else {
            return false;
        }
    }

    bool BActionManager::remove ( const BoxE::Core::BAsciiString &name ) {
        if ( !contains ( name ) ) {
            return false;
        }

        actions_hash_t::Iterator it = Actions.find ( name );
        Actions.erase ( it );

        ( *it )->onNameChanged().disconnect ( this, &BActionManager::actionNameChanged );

        return true;
    }

    bool BActionManager::remove ( BAbstractAction *action ) {
        if ( action == 0 ) {
            return false;
        }

        return remove ( action->getName() );
    }


    BActionManager::actions_hash_t::ConstIterator BActionManager::constBegin() const {
        return Actions.constBegin();
    }


    BActionManager::actions_hash_t::ConstIterator BActionManager::constEnd() const {
        return Actions.constEnd();
    }


    void BActionManager::actionNameChanged ( BAbstractAction *action, BoxE::Core::BAsciiString new_name ) {
        actions_hash_t::Iterator it = Actions.begin();
        while ( it != Actions.end() ) {
            if ( ( *it ) == action  ) {
                Actions.erase ( it );
                Actions.insert ( new_name, action );
                return;
            }
            it++;
        }
    }
}