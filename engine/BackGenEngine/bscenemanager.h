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


#ifndef BSCENEMANAGER_H
#define BSCENEMANAGER_H

#include <BoxE/BAsciiString>
#include <BoxE/bhash.h>

namespace BackGenEngine {
    class BLogger;
    class BScene;
}

namespace BackGenEngine {
    class BSceneManager {
        public:
            typedef BoxE::Core::BHash< BoxE::Core::BAsciiString, BScene * > scene_hash_t;
        public:
            BSceneManager ( BLogger *logger );
            ~BSceneManager();

            const scene_hash_t &getSceneHash() const {
                return SceneHash;
            }

            bool containScene ( BScene *scene ) const;
            bool containScene ( const BoxE::Core::BAsciiString &name ) const;

            bool insertScene ( BScene *scene );
            bool removeScene ( BScene *scene );
            BScene *getScene ( const BoxE::Core::BAsciiString &name );
        private:
            BLogger *Logger;
            scene_hash_t SceneHash;

        private:
            /*!
             * On tag name changed signal.
             * \param scene Pointer to scene.
             * \param new_name New name.
             */
            void onSceneNameChaned ( BScene *scene, BoxE::Core::BAsciiString new_name  );
    };
}

#endif // BSCENEMANAGER_H
