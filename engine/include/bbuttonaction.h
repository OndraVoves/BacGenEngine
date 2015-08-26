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


#ifndef BBUTTONACTION_H
#define BBUTTONACTION_H

#include <BoxE/BoxECore>

#include "babstractaction.h"
#include "babstractwindow.h"

namespace BackGenEngine {
    /*!
     * Button action.
     */
    class BButtonAction : public BAbstractAction {
        public:
            /*!
             * Create button action.
             * \param name Name.
             * \param button Button.
             * \param p_window Pointer to window.
             */
            BButtonAction ( const BoxE::Core::BAsciiString &name, BAbstractWindow::key_t button, BAbstractWindow *p_window );

            /*!
             * Destructor.
             */
            virtual ~BButtonAction();

            /*!
             * Get button.
             * \return Button.
             */
            BAbstractWindow::key_t getButton() const;

            /*!
             * Set button.
             * \param button Button.
             */
            void setButton ( BAbstractWindow::key_t button );

            /*!
             * Is key down?
             * \return key status.
             */
            bool isDown() const;

            /*!
             * Is key up?
             * \return key status.
             */
            bool isUp() const;

        private:
            BAbstractWindow::key_t Button;
            BAbstractWindow *pWindow;
    };

}

#endif // BBUTTONACTION_H
