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


#ifndef BRTTIOBJECT_H
#define BRTTIOBJECT_H

#include "brtti.h"

namespace BackGenEngine {

    class BRTTIObject {
            BGE_RTTI_DECLARATION
        public:
            BRTTIObject();
            ~BRTTIObject();

            bool isDerivedTypeOf ( const BRTTI &rtti ) const {
                return rttiType().isDerivedFrom ( rtti );
            }

            bool isExactlyTypeOf ( const BRTTI &rtti ) const {
                return rttiType().isExactlyFrom ( rtti );
            }

            bool isDerivedTypeOf ( const BRTTIObject *object ) const {
                if ( !object  ) {
                    return false;
                }
                return rttiType().isDerivedFrom ( object->rttiType() );
            }

            bool isExactlyTypeOf ( const BRTTIObject *object ) const {
                if ( !object  ) {
                    return false;
                }
                return rttiType().isExactlyFrom ( object->rttiType() );
            }
    };

    template< class T >
    T *BStaticCast ( BRTTIObject *object ) {
        return ( T * ) object;
    }

    template< class T >
    T *BDynamicCast ( BRTTIObject *object ) {
        return ( object && object->isDerivedTypeOf ( T::RTTIType ) ) ? ( T * ) object : 0;
    }

}
#endif // BRTTIOBJECT_H
