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


#ifndef BTAG_H
#define BTAG_H

#include <BoxE/BoxECore>

namespace BackGenEngine {
    class BObject;
}

namespace BackGenEngine {

    /*!
     * Tag class.
     */
    class BTag {
        public:
            typedef BoxE::Core::BHash< BoxE::Core::BAsciiString, BObject * > bobject_hash_t;

        public:
            /*!
             * Create tag.
             * \param name.
             */
            BTag ( const BoxE::Core::BAsciiString &name );

            /*!
             * Destructor.
             */
            ~BTag();

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

            /*!
             * Const begin object iterator.
             * \return Const begin iterator.
             */
            bobject_hash_t::ConstIterator constBegin() const;

            /*!
             * Const end object iterator.
             * \return Const end iterator.
             */
            bobject_hash_t::ConstIterator constEnd() const;

            /*!
             * Insert object.
             * \param object Pointer to object.
             * \return Insert status.
             */
            bool insertObject ( BObject *object );

            /*!
             * Remove object.
             * \param object Pointer to object.
             * \return Remove status.
             */
            bool removeObject ( BObject *object );

            /*!
             * Remove object.
             * \param name Object name.
             * \return Remove status.
             */
            bool removeObject ( const BoxE::Core::BAsciiString &name );

            /*!
             * Is object in?
             * \param object Pointer to object.
             * \return Is object in?
             */
            bool containObject ( BObject *object ) const;

            /*!
             * Is object in?
             * \param name Object name.
             * \return Is object in?
             */
            bool containObject ( const BoxE::Core::BAsciiString &name ) const;

            BObject *getObject ( const BoxE::Core::BAsciiString &name );

//Signals
        public:
            /*!
             * On name changed signal.
             * \return Signal.
             */
            BoxE::Core::BSignal2< BTag *, BoxE::Core::BAsciiString >& onNameChanged();

        protected:
            BoxE::Core::BSignal2< BTag *, BoxE::Core::BAsciiString > OnNameChanged;

        private:
            BoxE::Core::BAsciiString Name;
            bobject_hash_t ObjectsHash;

        private:
            /*!
             * Object name changed.
             * \param obj Object pointer.
             * \param new_name New name.
             */
            void objectNameChanged ( BObject *obj, BoxE::Core::BAsciiString new_name );
    };


}

#endif // BTAG_H
