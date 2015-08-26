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


#ifndef BVERTEX_H
#define BVERTEX_H

#include <BoxE/BVector2f>
#include <BoxE/BVector3f>
#include <BoxE/BVector4f>

namespace BackGenEngine {

    class BVertex {
        public:
            BVertex();
            BVertex ( const BVertex &other );
            BVertex ( const BoxE::Math::BVector3f &position, const BoxE::Math::BVector3f &normal, const BoxE::Math::BVector2f &texcoord, const BoxE::Math::BVector4f &color );
            ~BVertex();

            BoxE::Math::BVector3f &getPosition();
            const BoxE::Math::BVector3f &getPosition() const;

            BoxE::Math::BVector3f &getNormal();
            const BoxE::Math::BVector3f &getNormal() const;

            BoxE::Math::BVector2f &getTexCoord();
            const BoxE::Math::BVector2f &getTexCoord() const;

            BoxE::Math::BVector4f &getColor();
            const BoxE::Math::BVector4f &getColor() const;

        private:
            BoxE::Math::BVector3f Position;
            BoxE::Math::BVector3f Normal;
            BoxE::Math::BVector2f TexCoord;
            BoxE::Math::BVector4f Color;
    };

}
#endif // BVERTEX_H
