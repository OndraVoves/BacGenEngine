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


#ifndef BRTTI_H
#define BRTTI_H

#include <BoxE/BAsciiString>

#define BGE_RTTI_DECLARATION\
    public:\
    static const BackGenEngine::BRTTI RTTIType;\
    virtual const BackGenEngine::BRTTI& rttiType() const {\
        return RTTIType;\
    }\
     
#define BGE_RTTI_IMPLEMENTATION( namespace, class, baseclass )\
    const BackGenEngine::BRTTI class::RTTIType(  #namespace"::"#class, &baseclass::RTTIType )

namespace BackGenEngine {
    class BRTTI {
        public:
            BRTTI ( const BoxE::Core::BAsciiString &name, const BRTTI *base_type );
            ~BRTTI();

            BoxE::Core::BAsciiString name() const;

            bool isDerivedFrom ( const BRTTI &rtti ) const;
            bool isExactlyFrom ( const BRTTI &rtti ) const;

        private:
            BoxE::Core::BAsciiString Name;
            const BRTTI *BaseType;
    };
}

#endif // BRTTI_H
