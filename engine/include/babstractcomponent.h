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


#ifndef BABSTRACTCOMPONENT_H
#define BABSTRACTCOMPONENT_H

#include <BoxE/BoxECore>
#include "./brttiobject.h"

namespace BackGenEngine {
    class BObject;
    class BScene;
    class BAssetManager;
}

namespace BackGenEngine {
    /*!
     * Abstract component.
     */
    class BAbstractComponent : public BRTTIObject {
            BGE_RTTI_DECLARATION
        public:
            /*!
             * Constructor.
             */
            BAbstractComponent ( BScene *pc_scene );

            /*!
             * Destructor.
             */
            virtual ~BAbstractComponent();

            /*!
             * Component name.
             */
            virtual BoxE::Core::BAsciiString getName() const = 0;

            virtual BAbstractComponent *duplicate() const = 0;

            virtual BoxE::Core::BByteArray toByteArray();
            virtual bool fromByteArray ( const BoxE::Core::BByteArray &byte_array, BAssetManager *pc_asset_manager );

            /*!
             * Pointer to owner object.
             * \return If component have owner object return his pointer, else return 0;
             */
            BObject *getOwnerObject() const;

        protected:
            BScene *getScene() const;
        private:
            BObject *pOwnerObject;
            BScene *pcScene;

            friend class BObject;
    };
}
#endif // BABSTRACTCOMPONENT_H