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


#ifndef BLAYERSMANAGER_H
#define BLAYERSMANAGER_H

#include <BoxE/BoxECore>

#include "blayer.h"

namespace BackGenEngine {
    class BLogger;
}


namespace BackGenEngine {

    /*!
     * Layers manager.
     */
    class BLayersManager {
        public:
            typedef BoxE::Core::BHash< BoxE::Core::BAsciiString, BLayer * > blayer_hash_t;
            typedef BoxE::Core::BHash< BLayer::ELayerType, blayer_hash_t * > blayer_type_hash_t;
        public:
            /*!
             * Constructor.
             */
            BLayersManager ( BLogger *logger );

            /*!
             * Destructor.
             */
            ~BLayersManager();

            blayer_type_hash_t &layersTypeHash() ;

            /*!
             * Is layer in?
             * \param name Layer name.
             * \return Is layer in?
             */
            bool containLayer ( const BoxE::Core::BAsciiString &name  ) const;

            /*!
             * Get layer.
             * \param name Layer name.
             * \return Pointer to layer.
             */
            BLayer *getLayer ( const BoxE::Core::BAsciiString &name ) const;

            /*!
             * Create layer.
             * \param name Layer name.
             * \param type Layer type.
             * \return Pointer to new layer.
             */
            BLayer *createLayer ( const BoxE::Core::BAsciiString &name, BLayer::ELayerType type );

            /*!
             * Remove layer.
             * \param layer Pointer to layer.
             * \return Remove status.
             */
            bool removeLayer ( BLayer *layer );

            /*!
             * Remove layer.
             * \param name Layer name.
             * \return Remove status.
             */
            bool removeLayer ( const BoxE::Core::BAsciiString &name );

            BoxE::Core::BByteArray toByteArray();
            bool fromByteArray ( const BoxE::Core::BByteArray &byte_array );
        private:
            blayer_type_hash_t Layers;
            BLogger *Logger;

        private:
            /*!
             * Insert layer.
             * \param layer Layer pointer.
             * \return Insert status.
             */
            bool insertLayer ( BLayer *layer );

            /*!
             * On layer type changed.
             * \param layer Layer.
             * \param new_type New layer type.
             */
            void onLayerTypeChaned ( BLayer *layer, BLayer::ELayerType new_type );

            /*!
             * On layer name changed.
             * \param layer Layer.
             * \param new_name New name.
             */
            void onLayerNameChaned ( BLayer *layer, BoxE::Core::BAsciiString new_name  );
    };

}
#endif // BLAYERSMANAGER_H
