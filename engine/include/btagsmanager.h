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


#ifndef BTAGSMANAGER_H
#define BTAGSMANAGER_H

#include <BoxE/BoxECore>

#include "btag.h"

namespace BackGenEngine {
    class BLogger;
}

namespace BackGenEngine {
    /*!
     * Tags manager.
     */
    class BTagsManager {
        public:
            typedef BoxE::Core::BHash< BoxE::Core::BAsciiString, BTag * > btag_hash_t;
        public:
            /*!
             * Constructor.
             */
            BTagsManager ( BLogger *logger );

            /*!
             * Destructor.
             */
            ~BTagsManager();

            BTag &rootTag();

            /*!
             * Is tag in?
             * \param name Tag name.
             * \return True if tag is in else return false.
             */
            bool containTag ( const BoxE::Core::BAsciiString &name  ) const;

            /*!
             * Create tag.
             * \param name Tag name.
             * \return Pointer to new tag.
             */
            BTag *createTag ( const BoxE::Core::BAsciiString &name );

            /*!
             * Get tag.
             * \param name Name.
             * \return Pointer to tag.
             */
            BTag *getTag ( const BoxE::Core::BAsciiString &name ) ; // const

            /*!
             * Remove tag.
             * \param name Tag name.
             * \return Remove status.
             */
            bool removeTag ( const BoxE::Core::BAsciiString &name );

            /*!
             * Remove tag.
             * \param tag Pointer to tag.
             * \return Remove status.
             */
            bool removeTag ( BTag *tag );

            const btag_hash_t &tagsHash() const;

            BoxE::Core::BByteArray toByteArray();
            bool fromByteArray ( const BoxE::Core::BByteArray &byte_array );
        private:
            btag_hash_t Tags;
            BTag RootTag;
            BLogger *Logger;

        private:
            /*!
             * Insert tag.
             * \param tag Pointer to tag.
             * \return Insert status.
             */
            bool insertTag ( BTag *tag );

            /*!
             * On tag name changed signal.
             * \param tag Pointer to tag.
             * \param new_name New name.
             */
            void onTagNameChaned ( BTag *tag, BoxE::Core::BAsciiString new_name  );
    };

}

#endif // BTAGSMANAGER_H
