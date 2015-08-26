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


#ifndef BDYNAMICMODULESYSTEM_H
#define BDYNAMICMODULESYSTEM_H

#include "./babstractmodulesystem.h"
#include "./bmodulesheader.h"

#include <BoxE/bhash.h>

namespace BoxE {
    namespace Core {
        class BLibrary;
    }
}

namespace BackGenEngine {
    class BComponentModule;
    class BAssetModule;
    class BAssetLoaderModule;
    class BAssetSaverModule;
    class BAbstractRenderer;
    class BProject;
    class BScene;
}

namespace BackGenEngine {

    /*!
     *  Dynamic module system.
     */
    class BDynamicModuleSystem : public BAbstractModuleSystem {
        public:
            typedef BoxE::Core::BHash< BoxE::Core::BAsciiString, BComponentModule *> component_module_hash_t;
            typedef BoxE::Core::BHash< BoxE::Core::BAsciiString, BAssetModule *> asset_module_hash_t;
            typedef BoxE::Core::BHash< BoxE::Core::BAsciiString, BAssetLoaderModule *> asset_loader_module_hash_t;
            typedef BoxE::Core::BHash< BoxE::Core::BAsciiString, BAssetSaverModule *> asset_saver_module_hash_t;

        public:
            /*!
             * Constructor.
             * \param logger Pointer to logger.
             */
            BDynamicModuleSystem ( BLogger *logger );

            /*!
             * Destructor.
             */
            virtual ~BDynamicModuleSystem();

            /*!
             * Create component.
             * \param name Name.
             * \return Pointer to new component.
             */
            virtual BAbstractComponent *createComponent ( const BoxE::Core::BAsciiString &name, BScene *pc_scene );

            virtual BAbstractAsset *createAsset ( const BoxE::Core::BAsciiString &name, BProject *pc_project, BAbstractRenderer *pc_renderer,  BAssetManager *pc_asset_manager, BLogger *pc_logger );

            virtual bool loadAsset ( const BoxE::Core::BAsciiString &name, BAbstractAsset *asset, BoxE::Core::BIODevice *data, BAssetManager *pc_asset_manager, BLogger *pc_logger );
            virtual bool saveAsset ( const BoxE::Core::BAsciiString &name, BAbstractAsset *asset, BoxE::Core::BIODevice *data, BLogger *pc_logger );

            /*!
             * Load module.
             * \param path Module path.
             * \return Load status.
             */
            bool loadModule ( const BoxE::Core::BAsciiString &path );

            /*!
             * Unload module.
             * \param name Module name.
             * \return Unload status.
             */
            bool unloadModule ( const BoxE::Core::BAsciiString &name );

            component_module_hash_t::ConstIterator constComponentBegin() const;

            component_module_hash_t::ConstIterator constComponentEnd() const;

            const asset_module_hash_t &getAssetModuleHash() const;

            const asset_loader_module_hash_t &getAssetLoaderHash() const;
        private:
            /*!
             * Parse base header.
             * \param header Pointer to header.
             * \return Parse status.
             */
            bool parseBaseHeader ( BBaseModuleHeader_t *header );

            bool parseAssetLoaderHeader ( BAssetLoaderModuleHeader_t *header );
            bool parseAssetSaverHeader ( BAssetSaverModuleHeader_t *header );

            /*!
             * Insert component module.
             * \param lib Pointer to lib.
             * \param header Pointer to header.
             * \return Insert module.
             */
            bool insertComponentModule ( BoxE::Core::BLibrary *lib, BBaseModuleHeader_t *header );

            /*!
             * Unload all component.
             */
            void unloadAllComponent();

            bool insertAssetModule ( BoxE::Core::BLibrary *lib, BBaseModuleHeader_t *header );
            void unloadAllAsset();

            bool insertAssetLoaderModule ( BoxE::Core::BLibrary *lib, BBaseModuleHeader_t *base_header, BAssetLoaderModuleHeader_t *header );
            bool insertAssetSaverModule ( BoxE::Core::BLibrary *lib, BBaseModuleHeader_t *base_header, BAssetSaverModuleHeader_t *header );

        private:
            component_module_hash_t ComponentModuleHash;
            asset_module_hash_t AssetModuleHash;
            asset_loader_module_hash_t AssetLoaderModuleHash;
            asset_saver_module_hash_t AssetSaverModuleHash;
    };

}
#endif // BDYNAMICMODULESYSTEM_H
