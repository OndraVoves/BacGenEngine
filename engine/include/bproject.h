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


#ifndef BPROGRAM_H
#define BPROGRAM_H

#include <BoxE/BAsciiString>

#include "./bscenemanager.h"
#include "./bassetmanager.h"

namespace BackGenEngine {
    class BLogger;
    class BAbstractModuleSystem;
    class BAbstractWindow;
}

class BoxE::Core::BIODevice;

namespace BackGenEngine {
    class BProject {
        public:
            BProject ( BAbstractWindow *window, BAbstractModuleSystem *module_system, BLogger *logger );
            ~BProject();

            BoxE::Core::BAsciiString getName() const;

            BoxE::Core::BAsciiString getBaseDir(  ) const;

            void setName ( const BoxE::Core::BAsciiString &name );

            void setBaseDir ( const BoxE::Core::BAsciiString &dir );

            BSceneManager &getSceneManager( );

            BAbstractModuleSystem *getModuleSystem();

            BAssetManager &getAssetManager();

            BoxE::Core::BByteArray toByteArray();
            bool fromByteArray ( const BoxE::Core::BByteArray &byte_array );

        private:
            BoxE::Core::BAsciiString Name;
            BoxE::Core::BAsciiString BaseDir;
            BAssetManager AssetManager;
            BSceneManager SceneManager;
            BAbstractWindow *Window;
            BAbstractModuleSystem *ModuleSystem;
            BLogger *Logger;
    };
}

#endif // BPROGRAM_H
