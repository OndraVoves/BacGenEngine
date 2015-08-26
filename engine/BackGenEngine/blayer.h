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


#ifndef BLAYER_H
#define BLAYER_H

#include <BoxE/BoxECore>

namespace BackGenEngine {
    class BObject;
    class BLogger;
}

namespace BackGenEngine {

    class BLayer {
        public:
            typedef BoxE::Core::BHash< BoxE::Core::BAsciiString, BObject * > bobject_hash_t;

        public:
            typedef enum {
                NORMAL = 0,
                TRANSPARENT,
                GUI,
                FIRST_USER_DEFINED
            } ELayerType;

        public:
            /*!
             * Create layer.
             * \param new_name Name.
             * \param layer_type Layer type.
             */
            BLayer ( const BoxE::Core::BAsciiString &new_name, ELayerType layer_type, BLogger *pc_logger );

            /*!
             * Destructor.
             */
            ~BLayer();

            /*!
             * Get name.
             * \return Name.
             */
            BoxE::Core::BAsciiString getName() const;

            /*!
             * Get layer type.
             * \return Layer type.
             */
            ELayerType getLayerType() const;

            /*!
             * Set layer type.
            * \param layer_type Layer type.
            */
            void setLayerType ( ELayerType layer_type );

            /*!
             * Set name.
             * \param new_name New name.
             */
            void setName ( const BoxE::Core::BAsciiString &new_name );

            /*!
             * Const begin iterator.
             * \return Const begin iterator.
             */
            bobject_hash_t::ConstIterator constBegin() const;

            /*!
             * Const end iterator.
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

            //Signals
        public:
            /*!
             * On name changed signal.
             * \return Signal.
             */
            BoxE::Core::BSignal2< BLayer *, BoxE::Core::BAsciiString >& onNameChanged();

            /*!
             * On layer type changed signal.
             * \return Signal.
             */
            BoxE::Core::BSignal2< BLayer *, ELayerType >& onLayerTypeChanged();

        protected:
            BoxE::Core::BSignal2< BLayer *, BoxE::Core::BAsciiString > OnNameChanged;
            BoxE::Core::BSignal2< BLayer *, ELayerType > OnLayerTypeChanged;

        private:
            /*!
             * Object name changed.
             * \param obj Object pointer.
             * \param new_name New name.
             */
            void objectNameChanged ( BObject *obj, BoxE::Core::BAsciiString new_name );

        private:
            BLogger *pcLogger;
            BoxE::Core::BAsciiString Name;
            bobject_hash_t ObjectsHash;
            ELayerType LayerType;
    };

    /*!
     * Calc hash.
     * \param type Layer type.
     */
    extern long bCalcHash ( BLayer::ELayerType type );

}
#endif // BLAYER_H
