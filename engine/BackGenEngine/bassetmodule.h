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


#ifndef BASSETMODULE_H
#define BASSETMODULE_H

#include <BoxE/BLibrary>

namespace BackGenEngine {
    class BAbstractAsset;
    class BAbstractRenderer;
    class BAbstractModuleSystem;
    class BAssetManager;
    class BProject;
    class BLogger;
};

namespace BackGenEngine {
    class BAssetModule {
        public:
            BAssetModule ( BoxE::Core::BLibrary *library );

            ~BAssetModule();

            /*!
             * Load module.
             * \return Load status.
             */
            bool load();

            /*!
             * Create component.
             * \return Pointer to new component.
             */
            BAbstractAsset *create (  BProject *pc_project, BackGenEngine::BAbstractRenderer *pc_renderer, BLogger *pc_logger, BAbstractModuleSystem *module_system,  BAssetManager *pc_asset_manager );

        private:
            typedef BAbstractAsset * ( create_fce_t ) ( BProject *, BackGenEngine::BAbstractRenderer *,  BLogger *, BAbstractModuleSystem *,  BAssetManager *pc_asset_manager );
            create_fce_t *CreateFce;

        private:
            BoxE::Core::BLibrary *pLibrary;

    };
}

#endif // BASSETMODULE_H
