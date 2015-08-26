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


#ifndef BABSTRACTMODULESYSTEM_H
#define BABSTRACTMODULESYSTEM_H

#include <BoxE/BAsciiString>

namespace BackGenEngine {
    class BAbstractComponent;
    class BAbstractAsset;
    class BAbstractRenderer;
    class BAssetManager;
    class BLogger;
    class BScene;
    class BProject;
}

namespace BackGenEngine {

    /*!
     * Abstract module system.
     */
    class BAbstractModuleSystem {
        public:
            /*!
             * Constructor.
             * \param logger Pointer to logger.
             */
            BAbstractModuleSystem ( BLogger *logger );

            /*!
             * Destructor.
             */
            virtual ~BAbstractModuleSystem();

            /*!
             * Create component.
             * \param name Component name.
             */
            virtual BAbstractComponent *createComponent ( const BoxE::Core::BAsciiString &name, BScene *pc_scene ) = 0;

            virtual BAbstractAsset *createAsset ( const BoxE::Core::BAsciiString &name,  BProject *pc_project, BackGenEngine::BAbstractRenderer *pc_renderer, BAssetManager *pc_asset_manager, BLogger *pc_logger  ) = 0;
            virtual bool loadAsset ( const BoxE::Core::BAsciiString &name, BAbstractAsset *asset, BoxE::Core::BIODevice *data, BAssetManager *pc_asset_manager, BLogger *pc_logger ) = 0;
            virtual bool saveAsset ( const BoxE::Core::BAsciiString &name, BAbstractAsset *asset, BoxE::Core::BIODevice *data, BLogger *pc_logger ) = 0;

        protected:
            BLogger *Logger;
    };

}
#endif // BABSTRACTMODULESYSTEM_H
