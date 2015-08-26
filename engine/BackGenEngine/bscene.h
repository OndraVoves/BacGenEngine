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


#ifndef BSCENE_H
#define BSCENE_H

#include "./btagsmanager.h"
#include "./blayersmanager.h"
#include "babstractrenderer.h"

namespace BackGenEngine {
    class BLogger;
    class BObject;
    class BAbstractModuleSystem;
    class BAbstractRenderer;
    class BAssetManager;
}

namespace BackGenEngine {

    class BScene  {
        public:
            BScene ( BAbstractRenderer *pc_renderer, BLogger *logger );
            ~BScene();

            /*!
             * Get name.
             * \return Name.
             */
            BoxE::Core::BAsciiString getName() const;

            /*!
             * Set name.
             * \param new_name New name.
             */
            void setName ( const BoxE::Core::BAsciiString &new_name );

            void setActiveCameraObject ( BObject *pc_camera );
            BObject *getActiveCameraObject();

            BLayersManager &getLayersManager();
            BTagsManager &getTagsManager();

            BAbstractRenderer *getRenderer();

            BoxE::Core::BByteArray toByteArray();
            bool fromByteArray ( const BoxE::Core::BByteArray &byte_array, BAbstractModuleSystem *pc_modules_system, BAssetManager *pc_asset_manager );
//Signals
        public:
            /*!
             * On name changed signal.
             * \return Signal.
             */
            BoxE::Core::BSignal2< BScene *, BoxE::Core::BAsciiString >& onNameChanged();

        protected:
            BoxE::Core::BSignal2< BScene *, BoxE::Core::BAsciiString > OnNameChanged;

        private:
            BoxE::Core::BAsciiString Name;

            BTagsManager TagsManager;
            BLayersManager LayersManager;

            BAbstractRenderer *pcRenderer;

            BObject *pcActiveCameraObject;
    };

}

#endif // BSCENE_H
