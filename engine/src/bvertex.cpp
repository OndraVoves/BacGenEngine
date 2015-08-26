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


#include "../include/bvertex.h"

namespace BackGenEngine {
    BVertex::BVertex() : Color ( 1.0f, 1.0f, 1.0f, 1.0f ) {
    }

    BVertex::BVertex ( const BVertex &other )
        : Position ( other.Position ), Normal ( other.Normal ), TexCoord ( other.TexCoord ), Color ( other.Color ) {
    }

    BVertex::BVertex ( const BoxE::Math::BVector3f &position, const BoxE::Math::BVector3f &normal, const BoxE::Math::BVector2f &texcoord, const BoxE::Math::BVector4f &color )
        : Position ( position ), Normal ( normal ), TexCoord ( texcoord ), Color ( color ) {
    }

    BVertex::~BVertex() {
    }

    BoxE::Math::BVector3f &BVertex::getPosition() {
        return Position;
    }

    const BoxE::Math::BVector3f &BVertex::getPosition() const {
        return Position;
    }

    BoxE::Math::BVector3f &BVertex::getNormal() {
        return Normal;
    }

    const BoxE::Math::BVector3f &BVertex::getNormal() const {
        return Normal;
    }

    BoxE::Math::BVector2f &BVertex::getTexCoord() {
        return TexCoord;
    }

    const BoxE::Math::BVector2f &BVertex::getTexCoord() const {
        return TexCoord;
    }

    BoxE::Math::BVector4f &BVertex::getColor() {
        return Color;
    }

    const BoxE::Math::BVector4f &BVertex::getColor() const {
        return Color;
    }
}