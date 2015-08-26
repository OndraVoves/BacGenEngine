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


#ifndef BASSETLOADERMODULE_H
#define BASSETLOADERMODULE_H

#include <BoxE/BLibrary>

namespace BackGenEngine {
    class BAbstractAsset;
    class BAssetManager;
    class BLogger;
};

namespace BackGenEngine {

    class BAssetLoaderModule {
        public:
            BAssetLoaderModule ( BoxE::Core::BLibrary *library, const BoxE::Core::BAsciiString &asset_name  );
            ~BAssetLoaderModule();

            bool load();
            bool load ( BAbstractAsset *asset, BoxE::Core::BIODevice *data, BAssetManager *pc_asset_manager, BLogger *pc_logger );

            const BoxE::Core::BAsciiString  &getAssetType() const;
        private:
            typedef bool ( load_fce_t ) ( BAbstractAsset *asset, BoxE::Core::BIODevice *data, BAssetManager *pc_asset_manager, BLogger *pc_logger );
            load_fce_t *LoadFce;

        private:
            BoxE::Core::BLibrary *pLibrary;
            BoxE::Core::BAsciiString AssetName;
    };

}

#endif // BASSETLOADERMODULE_H
