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


#ifndef BABSTRACTASSET_H
#define BABSTRACTASSET_H

#include <BoxE/BAsciiString>
#include <BoxE/BSignalSlot>

namespace BackGenEngine {
    class BAbstractModuleSystem;
    class BAbstractRenderer;
    class BAssetManager;
    class BProject;
    class BLogger;
}

namespace BackGenEngine {

    /*!
     * Abstract asset class.
     */
    class BAbstractAsset {
        public:

            /*!
             * Constructor.
             */
            BAbstractAsset ( BProject *pc_project, BackGenEngine::BAbstractRenderer *pc_renderer, BLogger *pc_logger, BAbstractModuleSystem *module_system, BAssetManager *pc_asset_manager );

            /*!
             * Destructor.
             */
            virtual ~BAbstractAsset();

            virtual BoxE::Core::BAsciiString getInterfaceType() const = 0;
            virtual BoxE::Core::BAsciiString getAssetType() const = 0;

            /*!
             * Get asset name.
             * \return Name.
             */
            BoxE::Core::BAsciiString getName() const;

            /*!
             * Set name.
             * \param name Name.
             */
            void setName ( const BoxE::Core::BAsciiString &name );

            /*!
             * Get path.
             * \return Path.
             */
            BoxE::Core::BAsciiString getPath() const;

            /*!
             * Set path.
             * \param path New path.
             */
            void setPath ( const BoxE::Core::BAsciiString &path );

            /*!
             * Is asset loaded?
             * \return Asset loaded?
             */
            bool isLoaded() const;

            virtual bool realod();

            virtual bool use();
            virtual bool unuse();

            bool save();

        protected:
            virtual bool load();
            virtual bool unload() = 0;

            void setLoaded ( bool loaded );

            BAbstractModuleSystem *getModuleSystem();
            BLogger *getLogger();
            BProject *getProject();
            BAssetManager *getAssetManager();
// signals
        private:
            BoxE::Core::BSignal0 OnRealod;
            BoxE::Core::BSignal0 OnDestroy;
            BoxE::Core::BSignal2< BAbstractAsset *, BoxE::Core::BAsciiString > OnNameChanged;

        public:
            /*!
             * On reload signal.
             */
            BoxE::Core::BSignal0 &onReload();

            BoxE::Core::BSignal0 &onDestroy();

            /*!
             * On name changed signal.
             * \return Signal.
             */
            BoxE::Core::BSignal2< BAbstractAsset *, BoxE::Core::BAsciiString >& onNameChanged();

        private:
            BProject *pcProject;
            BLogger *pcLogger;
            BAbstractModuleSystem *ModuleSystem;
            BAssetManager *pcAssetManager;

            BoxE::Core::BAsciiString Name;
            BoxE::Core::BAsciiString Path;
            bool Loaded;

    };

}
#endif // BABSTRACTASSET_H
