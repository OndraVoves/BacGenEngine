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


#include "../include/bcomponentmodule.h"

namespace BackGenEngine {
    BComponentModule::BComponentModule ( BoxE::Core::BLibrary *library  ) : CreateFce ( 0 ), pLibrary ( library ) {
    }

    BComponentModule::~BComponentModule() {
        delete pLibrary;
    }

    bool BComponentModule::load() {
        CreateFce =  ( create_fce_t * ) pLibrary->resolv ( "createComponent" );
        if ( CreateFce == 0 ) {
            return false;
        }
        return true;
    }

    BAbstractComponent *BComponentModule::create ( BScene *pc_scene ) {
        if ( CreateFce == 0 ) {
            return 0;
        } else {
            return CreateFce ( pc_scene );
        }
    }
}

