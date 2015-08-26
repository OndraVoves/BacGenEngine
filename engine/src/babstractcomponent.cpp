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


#include "../include/babstractcomponent.h"
#include "../include/bobject.h"

namespace BackGenEngine {
    BGE_RTTI_IMPLEMENTATION ( BackGenEngine, BAbstractComponent, BRTTIObject );

    BAbstractComponent::BAbstractComponent ( BScene *pc_scene ) : pcScene ( pc_scene ) {
    }

    BAbstractComponent::~BAbstractComponent() {
        if ( pOwnerObject != 0 ) {
            pOwnerObject->removeComponent ( this );
        }
    }

    BObject *BAbstractComponent::getOwnerObject() const {
        return pOwnerObject;
    }

    BScene *BAbstractComponent::getScene() const {
        return pcScene;
    }

    BoxE::Core::BByteArray BAbstractComponent::toByteArray() {
        return "\n";
    }

    bool BAbstractComponent::fromByteArray ( const BoxE::Core::BByteArray &byte_array, BAssetManager *pc_asset_manager ) {
        return true;
    }

}
