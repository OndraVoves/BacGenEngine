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


#ifndef BACTIONMANAGER_H
#define BACTIONMANAGER_H

#include <BoxE/BoxECore>

namespace BackGenEngine {
    class BAbstractAction;
}

namespace BackGenEngine {

    /*!
     * Action manager.
     */
    class BActionManager {
        public:
            typedef BoxE::Core::BHash< BoxE::Core::BAsciiString, BAbstractAction * > actions_hash_t;

        public:
            /*!
             * Constructor.
             */
            BActionManager();

            /*!
             * Destructor.
             */
            ~BActionManager();

            /*!
             * Find action by name.
             * \param name Name.
             * \return Pointer to action or return 0.
             */
            BAbstractAction *find ( const BoxE::Core::BAsciiString &name );

            /*!
             * Contains action?
             * \param name Name.
             * \return True if action is in.
             */
            bool contains ( const BoxE::Core::BAsciiString &name ) const;

            /*!
             * Insert action.
             * \param action Pointer to action.
             * \return Insert status.
             */
            bool insert ( BAbstractAction *action );

            /*!
             * Remove action.
             * \param action Pointer to action.
             * \return Remove status.
             */
            bool remove ( BAbstractAction *action );

            /*!
             * Remove action.
             * \param name Name.
             * \return Remove status.
             */
            bool remove ( const BoxE::Core::BAsciiString &name );

            /*!
             * Get const begin iterator.
             * \return Const iterator.
             */
            actions_hash_t::ConstIterator constBegin() const;

            /*!
             * Get const end iterator.
             * \return Const iterator.
             */
            actions_hash_t::ConstIterator constEnd() const;

        private:
            actions_hash_t Actions;

            void actionNameChanged ( BAbstractAction *action, BoxE::Core::BAsciiString new_name );
    };

}

#endif // BACTIONMANAGER_H
