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


#ifndef BABSTRACTACTION_H
#define BABSTRACTACTION_H

#include <BoxE/BoxECore>

namespace BackGenEngine {

    class BAbstractAction {
        public:
            BAbstractAction ( const BoxE::Core::BAsciiString &name );

            virtual ~BAbstractAction();

            /*!
             * Get name.
             * \return Name.
             */
            BoxE::Core::BAsciiString getName() const;

            /*!
             * Set name.
             * \param name Name.
             */
            void setName ( const BoxE::Core::BAsciiString &name );

            //Signals
        public:
            /*!
             * On name changed signal.
             * \return Signal.
             */
            BoxE::Core::BSignal2< BAbstractAction *, BoxE::Core::BAsciiString >& onNameChanged();

        protected:
            BoxE::Core::BSignal2< BAbstractAction *, BoxE::Core::BAsciiString > OnNameChanged;

        private:
            BoxE::Core::BAsciiString Name;
    };


}
#endif // BABSTRACTACTION_H
