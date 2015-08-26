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


#include "../include/bscenemanager.h"
#include "../include/bscene.h"
#include "../include/blogger.h"

namespace BackGenEngine {
    BSceneManager::BSceneManager ( BLogger *logger ) : Logger ( logger ) {

    }

    BSceneManager::~BSceneManager() {
    }

    bool BSceneManager::containScene ( BScene *scene ) const {
        scene_hash_t::ConstIterator it = SceneHash.constBegin();
        while ( it != SceneHash.constEnd() ) {
            if ( ( *it ) == scene ) {
                return true;
            }
            ++it;
        }
        return false;
    }

    bool BSceneManager::containScene ( const BoxE::Core::BAsciiString &name ) const {
        return SceneHash.contains (  name );
    }

    bool BSceneManager::insertScene ( BScene *scene ) {
        if ( scene == 0 ) {
            return false;
        }

        if ( containScene ( scene ) ) {
            return false;
        }

        if ( SceneHash.insert ( scene->getName(), scene ) ) {
            scene->onNameChanged().connect ( this, &BSceneManager::onSceneNameChaned );
            Logger->debug ( BoxE::Core::BAsciiString ( "Inserting scene '" ) << scene->getName() << "' [ OK ]" );
            return true;
        } else {
            Logger->error ( BoxE::Core::BAsciiString ( "Inserting scene '" ) << scene->getName() << "' [ BAD ]" );
            return false;
        }
    }

    bool BSceneManager::removeScene ( BScene *scene ) {
        if ( scene == 0 ) {
            return false;
        }

        scene_hash_t::Iterator it = SceneHash.find ( scene->getName() );

        if ( it != SceneHash.end() ) {
            ( *it )->onNameChanged().disconnect ( this, &BSceneManager::onSceneNameChaned );
            SceneHash.erase ( it );

            Logger->debug ( BoxE::Core::BAsciiString ( "Removing scene '" ) << scene->getName() << "' [ OK ]" );
            return true;
        } else {
            Logger->debug ( BoxE::Core::BAsciiString ( "Removing scene '" ) << scene->getName() << "' [ BAD ]" );
            return false;
        }
    }


    BScene *BSceneManager::getScene ( const BoxE::Core::BAsciiString &name ) {
        scene_hash_t::Iterator it = SceneHash.find ( name );
        if ( it != SceneHash.end() ) {
            return ( *it );
        } else {
            return 0;
        }
    }

    void BSceneManager::onSceneNameChaned ( BScene *scene, BoxE::Core::BAsciiString new_name  ) {
        scene_hash_t::Iterator it = SceneHash.begin();
        while ( it != SceneHash.end() ) {
            if ( ( *it ) == scene ) {
                SceneHash.erase ( it );
                SceneHash.insert ( new_name, scene );
                return;
            }
            ++it;
        }
    }

}