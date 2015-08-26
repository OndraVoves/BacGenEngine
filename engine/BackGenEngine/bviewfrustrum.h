/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2011  Ondra Voves <email>

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


#ifndef BVIEWFRUSTRUM_H
#define BVIEWFRUSTRUM_H

#include <BoxE/BPlane3f>
#include <BoxE/BMatrix4x4f>

// TODO make beter

namespace BackGenEngine {
    class BViewFrustrum {
        public:
            typedef enum {
                Far = 0,
                Near,
                Left,
                Right,
                Bottom,
                Top,
                VFP_Count
            } EViewFrustrumPlane;

        public:
            BViewFrustrum( );
            BViewFrustrum ( const BViewFrustrum &other );


            BoxE::Math::BVector3f getFarLeftUp() const;
            BoxE::Math::BVector3f getFarLeftDown() const;
            BoxE::Math::BVector3f getFarRightUp() const;
            BoxE::Math::BVector3f getFarRightDown() const;

            BoxE::Math::BVector3f getNearLeftUp() const;
            BoxE::Math::BVector3f getNearLeftDown() const;
            BoxE::Math::BVector3f getNearRightUp() const;
            BoxE::Math::BVector3f getNearRightDown() const;

            void fromMatrix ( const BoxE::Math::BMatrix4x4f &matrix );

        private:
            BoxE::Math::BPlane3f aPlanes[ VFP_Count ];
    };
}

#endif // BVIEWFRUSTRUM_H
