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

#ifndef BTRANSFORMATIONCOMPONENT_H
#define BTRANSFORMATIONCOMPONENT_H

#include <BoxE/BoxECore>

#include <BackGenEngine/babstractcomponent.h>
#include <BackGenEngine/bmodulesheader.h>

class BTransformationComponent : public BackGenEngine::BAbstractComponent {
        BGE_RTTI_DECLARATION
    public:
        BTransformationComponent ( BackGenEngine::BScene *pc_scene );
        virtual ~BTransformationComponent();

        virtual BoxE::Core::BAsciiString getName() const {
            return "Transformation";
        }

        const BoxE::Math::BVector3f &position() const {
            return Position;
        }

        BoxE::Math::BVector3f &position() {
            return Position;
        }

        const BoxE::Math::BVector3f &rotation() const {
            return Rotation;
        }

        BoxE::Math::BVector3f &rotation() {
            return Rotation;
        }

        const BoxE::Math::BVector3f &scale() const {
            return Scale;
        }

        BoxE::Math::BVector3f &scale() {
            return Scale;
        }

        BoxE::Math::BMatrix4x4f getObjectSpaceMatrix() const;

        virtual BAbstractComponent *duplicate() const;

        virtual BoxE::Core::BByteArray toByteArray();
        virtual bool fromByteArray ( const BoxE::Core::BByteArray &byte_array, BackGenEngine::BAssetManager *pc_asset_manager );

    private:
        BoxE::Math::BVector3f Position;
        BoxE::Math::BVector3f Rotation;
        BoxE::Math::BVector3f Scale;
};


#endif /* BTRANSFORMATIONCOMPONENT_H */
