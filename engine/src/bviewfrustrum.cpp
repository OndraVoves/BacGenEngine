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


#include "../include/bviewfrustrum.h"


namespace BackGenEngine {

    BViewFrustrum::BViewFrustrum() {
    }

    BViewFrustrum::BViewFrustrum ( const BViewFrustrum &other ) {
        for ( int i = 0; i < VFP_Count; i++ ) {
            aPlanes[ i ] = other.aPlanes[ i ];
        }
    }

    BoxE::Math::BVector3f BViewFrustrum::getFarLeftUp() const {
        BoxE::Math::BVector3f out_point;

        aPlanes[ Far ].getIntersectionWithPlanes ( aPlanes[Top], aPlanes[Left], out_point );

        return out_point;
    }

    BoxE::Math::BVector3f BViewFrustrum::getFarLeftDown() const {
        BoxE::Math::BVector3f out_point;

        aPlanes[ Far ].getIntersectionWithPlanes ( aPlanes[Bottom], aPlanes[Left], out_point );

        return out_point;
    }

    BoxE::Math::BVector3f BViewFrustrum::getFarRightUp() const {

        BoxE::Math::BVector3f out_point;

        aPlanes[ Far ].getIntersectionWithPlanes ( aPlanes[Top], aPlanes[Right], out_point );

        return out_point;
    }

    BoxE::Math::BVector3f BViewFrustrum::getFarRightDown() const {
        BoxE::Math::BVector3f out_point;

        aPlanes[ Far ].getIntersectionWithPlanes ( aPlanes[Bottom], aPlanes[Right], out_point );

        return out_point;
    }

    BoxE::Math::BVector3f BViewFrustrum::getNearLeftUp() const {
        BoxE::Math::BVector3f out_point;

        aPlanes[ Near ].getIntersectionWithPlanes ( aPlanes[Top], aPlanes[Left], out_point );

        return out_point;
    }

    BoxE::Math::BVector3f BViewFrustrum::getNearLeftDown() const {
        BoxE::Math::BVector3f out_point;

        aPlanes[ Near ].getIntersectionWithPlanes ( aPlanes[Bottom], aPlanes[Left], out_point );

        return out_point;
    }

    BoxE::Math::BVector3f BViewFrustrum::getNearRightUp() const {

        BoxE::Math::BVector3f out_point;

        aPlanes[ Near ].getIntersectionWithPlanes ( aPlanes[Top], aPlanes[Right], out_point );

        return out_point;
    }

    BoxE::Math::BVector3f BViewFrustrum::getNearRightDown() const {
        BoxE::Math::BVector3f out_point;

        aPlanes[ Near ].getIntersectionWithPlanes ( aPlanes[Bottom], aPlanes[Right], out_point );

        return out_point;
    }

    void BViewFrustrum::fromMatrix ( const BoxE::Math::BMatrix4x4f &matrix ) {
        BoxE::Math::BVector3f v;

        v.setXYZ ( matrix.constRow4().x() + matrix.constRow1().x(),
                   matrix.constRow4().y() + matrix.constRow1().y(),
                   matrix.constRow4().z() + matrix.constRow1().z() );

        aPlanes[ Left ].normal ( -v );
        aPlanes[ Left ].d ( - ( matrix.constRow4().w() + matrix.constRow1().w() ) );
        aPlanes[ Left ].normalize();

        v.setXYZ ( matrix.constRow4().x() - matrix.constRow1().x(),
                   matrix.constRow4().y() - matrix.constRow1().y(),
                   matrix.constRow4().z() - matrix.constRow1().z() );

        aPlanes[ Right ].normal ( - v );
        aPlanes[ Right ].d ( - ( matrix.constRow4().w() - matrix.constRow1().w() ) );
        aPlanes[ Right ].normalize();


        v.setXYZ ( matrix.constRow4().x() - matrix.constRow2().x(),
                   matrix.constRow4().y() - matrix.constRow2().y(),
                   matrix.constRow4().z() - matrix.constRow2().z() );

        aPlanes[ Top ].normal ( -v );
        aPlanes[ Top ].d ( - ( matrix.constRow4().w() - matrix.constRow2().w() ) );
        aPlanes[ Top ].normalize();


        v.setXYZ ( matrix.constRow4().x() + matrix.constRow2().x(),
                   matrix.constRow4().y() + matrix.constRow2().y(),
                   matrix.constRow4().z() + matrix.constRow2().z() );

        aPlanes[ Bottom ].normal ( -v  );
        aPlanes[ Bottom ].d ( - ( matrix.constRow4().w() + matrix.constRow2().w() )  );
        aPlanes[ Bottom ].normalize();


        v.setXYZ ( matrix.constRow4().x() - matrix.constRow3().x(),
                   matrix.constRow4().y() - matrix.constRow3().y(),
                   matrix.constRow4().z() - matrix.constRow3().z() );

        aPlanes[ Far ].normal ( -v );
        aPlanes[ Far ].d ( - ( matrix.constRow4().w() - matrix.constRow3().w() )  );
        aPlanes[ Far ].normalize();

        aPlanes[ Near ].normal ( -matrix.constRow3().toVector3f() );
        aPlanes[ Near ].d ( - matrix.constRow3().w()  );
        aPlanes[ Near ].normalize();
    }

}
