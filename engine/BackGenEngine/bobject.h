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


#ifndef BOBJECT_H
#define BOBJECT_H

#include <BoxE/BoxECore>

#include "./brttiobject.h"
#include "./babstractcomponent.h"


namespace BackGenEngine {
    class BTag;
    class BLayer;
    class BLayersManager;
    class BTagsManager;
    class BAssetManager;
    class BAbstractModuleSystem;
}

namespace BackGenEngine {

    /*!
     * Object class.
     */
    class BObject {
        public:
            typedef BoxE::Core::BVector< BAbstractComponent * > component_vector_t;
            typedef BoxE::Core::BLinkedList < BObject * > objects_list_t;
            typedef BoxE::Core::BHash< BoxE::Core::BAsciiString , BTag * > btags_hash_t;

        public:
            /*!
             * Constructor.
             */
            BObject();

            /*!
             * Constructor.
             * \param new_name Name.
             * \param parent Pointer to parent object.
             */
            BObject ( const BoxE::Core::BAsciiString &new_name, BObject *parent = 0 );

            /*!
             * Destructor.
             */
            ~BObject();

            /*!
             * Get name.
             * \return Name.
             */
            BoxE::Core::BAsciiString getName( ) const;

            /*!
             * Set name.
             * \param new_name Name.
             */
            void setName ( const BoxE::Core::BAsciiString &new_name );

            /*!
             * Get pointer to parent object.
             * \return Pointer to parent object.
             */
            BObject *getParent( ) const ;

            /*!
             * Set parent.
             * \param p Pointer to parent.
             */
            void setParent ( BObject *p );

            // Objects.
            const objects_list_t &getObjectsList() const;

            // COmponents.
            const component_vector_t &getComponentVector() const;

            /*!
             * Insert component.
             * \param component Component pointer.
             * \return Insert status.
             */
            bool insertComponent ( BAbstractComponent *component );

            /*!
             * Remove component.
             * \param component Component pointer.
             * \return Remove status.
             */
            bool removeComponent ( BAbstractComponent *component );


            /*!
             * Get component by name.
             * \param name Family name.
             * \return Pointer to component.
             */
            BAbstractComponent *getComponentByName ( const BoxE::Core::BAsciiString &name );

            template< class T >
            T *getComponent() {
                component_vector_t::Iterator it = Components.begin();
                while ( it != Components.end() ) {
                    if ( ( *it )->isDerivedTypeOf ( T::RTTIType ) ) {
                        return BStaticCast< T > ( *it );
                    }
                    ++it;
                }
                return 0;
            }

            /*!
             * Is object in tag?
             * \param name Tag name.
             * \return If object in tag return true else return false.
             */
            bool isInTag ( const BoxE::Core::BAsciiString &name );

            /*!
             * Get layer pointer.
             * \return Pointer to layer.
             */
            BLayer *layer() const;

            const btags_hash_t &tagsHash() const;

            BoxE::Core::BByteArray toByteArray();
            bool fromByteArray ( const BoxE::Core::BByteArray &byte_array, BLayersManager *pc_layers_manager, BTagsManager *pc_tags_manager, BAbstractModuleSystem *pc_modules_system, BScene *pc_scene, BAssetManager *pc_asset_manager );

            BObject *duplicate();

            //Signals
        public:
            /*!
             * On name changed signal.
             * \return Signal.
             */
            BoxE::Core::BSignal2< BObject *, BoxE::Core::BAsciiString >& onNameChanged();

        protected:
            BoxE::Core::BSignal2< BObject *, BoxE::Core::BAsciiString > OnNameChanged;

        private:
            BoxE::Core::BAsciiString Name;
            BObject *pParent;

            component_vector_t Components;
            objects_list_t ChildObjects;

            btags_hash_t Tags;
            BLayer *pLayer;

        private:
            friend class BTag;

            /*!
             * Add tag.
             * \param tag Pointer to tag.
             */
            void addTag ( BTag *tag );

            /*!
             * Remove tag.
             * \param tag Pointer to tag.
             */
            void removeTag ( BTag *tag );

            /*!
             * Tag name changed.
             * \param tag Pointer to tag.
             * \param new_name New name.
             */
            void tagNameChanged ( BTag *tag, BoxE::Core::BAsciiString new_name );

            friend class BLayer;

            /*!
             * Set Layer.
             * \param layer Pointer to layer.
             */
            void setLayer ( BLayer *layer );



        private:
            /*!
             * Remove child object.
             * \param obj Pointer to object.
             */
            void removeChild ( BObject *obj );

    };

}
#endif // BOBJECT_H
