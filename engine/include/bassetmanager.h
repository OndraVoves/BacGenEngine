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


#ifndef BASSETMANAGER_H
#define BASSETMANAGER_H

#include <BoxE/BAsciiString>
#include <BoxE/bhash.h>

namespace BackGenEngine {
    class BAbstractAsset;
    class BAbstractRenderer;
    class BAbstractModuleSystem;
    class BProject;
    class BLogger;
}

namespace BackGenEngine {

    class BAssetManager {
        public:
            typedef BoxE::Core::BHash< BoxE::Core::BAsciiString, BAbstractAsset *  > asset_hash_t;

            BAssetManager ( BProject *pc_project, BLogger *logger );
            ~BAssetManager();

            asset_hash_t::ConstIterator constBegin() const;

            asset_hash_t::ConstIterator constEnd() const;

            bool containAsset ( const BoxE::Core::BAsciiString &name ) const;

            BAbstractAsset *getAsset ( const BoxE::Core::BAsciiString &name );

            bool insertAsset ( BAbstractAsset *asset );
            bool removeAsset ( BAbstractAsset *asset );
            bool removeAsset ( const BoxE::Core::BAsciiString &name ) {
                return removeAsset ( getAsset ( name ) );
            }

            BoxE::Core::BByteArray toByteArray();
            bool fromByteArray ( const BoxE::Core::BByteArray &byte_array, BackGenEngine::BAbstractRenderer *pc_renderer );

        private:
            asset_hash_t AssetHash;
            BProject *pcProject;
            BLogger *Logger;

        private:
            void onAssetNameChaned ( BAbstractAsset *asset, BoxE::Core::BAsciiString new_name  );
    };

}

#endif // BASSETMANAGER_H
