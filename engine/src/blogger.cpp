/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) <year>  <name of author>

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

#include "../include/blogger.h"


namespace BackGenEngine {

    BLogger::BLogger() {
    }

    BLogger::~BLogger() {
    }

    void BLogger::info ( const BoxE::Core::BAsciiString &info ) const {
        fprintf ( stdout, "(I): %s\n", info.constData() );
    }

    void BLogger::warning ( const BoxE::Core::BAsciiString &warning ) const {
        fprintf ( stdout, "(W): %s\n", warning.constData() );
    }

    void BLogger::error ( const BoxE::Core::BAsciiString &error ) const {
        fprintf ( stderr, "(E): %s\n", error.constData() );
    }

    void BLogger::debug ( const BoxE::Core::BAsciiString &debug ) const {
        fprintf ( stdout, "(D): %s\n", debug.constData() );
    }


}

