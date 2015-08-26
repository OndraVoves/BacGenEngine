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

#ifndef BABSTRACTWINDOW_H
#define BABSTRACTWINDOW_H

#include <BoxE/BoxECore>
#include <BoxE/BoxECore>

namespace BackGenEngine {
    class BLogger;
}

namespace BackGenEngine {

    class BAbstractWindow {
        public:
            typedef BoxE::Math::BVector3f screen_resolution_t;
            typedef int key_t;
            typedef int mouse_button_t;

        public:
            static const key_t BK_UNKNOWN;
            static const key_t BK_BACKSPACE;
            static const key_t BK_TAB;
            static const key_t BK_CLEAR;
            static const key_t BK_RETURN;
            static const key_t BK_PAUSE;
            static const key_t BK_ESCAPE;
            static const key_t BK_SPACE;
            static const key_t BK_EXCLAIM;
            static const key_t BK_QUOTEDBL;
            static const key_t BK_HASH;
            static const key_t BK_DOLLAR;
            static const key_t BK_AMPERSAND;
            static const key_t BK_QUOTE;
            static const key_t BK_LEFTPAREN;
            static const key_t BK_RIGHTPARE;
            static const key_t BK_ASTERISK;
            static const key_t BK_PLUS;
            static const key_t BK_COMMA;
            static const key_t BK_MINUS;
            static const key_t BK_PERIOD;
            static const key_t BK_SLASH;
            static const key_t BK_0;
            static const key_t BK_1;
            static const key_t BK_2;
            static const key_t BK_3;
            static const key_t BK_4;
            static const key_t BK_5;
            static const key_t BK_6;
            static const key_t BK_7;
            static const key_t BK_8;
            static const key_t BK_9;
            static const key_t BK_COLON;
            static const key_t BK_SEMICOLON;
            static const key_t BK_LESS;
            static const key_t BK_EQUALS;
            static const key_t BK_GREATER;
            static const key_t BK_QUESTION;
            static const key_t BK_AT;

            static const key_t BK_LEFTBRACKET;
            static const key_t BK_BACKSLASH;
            static const key_t BK_RIGHTBRACKET;
            static const key_t BK_CARET;
            static const key_t BK_UNDERSCORE;
            static const key_t BK_BACKQUOTE;
            static const key_t BK_a;
            static const key_t BK_b;
            static const key_t BK_c;
            static const key_t BK_d;
            static const key_t BK_e;
            static const key_t BK_f;
            static const key_t BK_g;
            static const key_t BK_h;
            static const key_t BK_i;
            static const key_t BK_j;
            static const key_t BK_k;
            static const key_t BK_l;
            static const key_t BK_m;
            static const key_t BK_n;
            static const key_t BK_o;
            static const key_t BK_p;
            static const key_t BK_q;
            static const key_t BK_r;
            static const key_t BK_s;
            static const key_t BK_t;
            static const key_t BK_u;
            static const key_t BK_v;
            static const key_t BK_w;
            static const key_t BK_x;
            static const key_t BK_y;
            static const key_t BK_z;
            static const key_t BK_DELETE;

            static const key_t BK_KP0;
            static const key_t BK_KP1;
            static const key_t BK_KP2;
            static const key_t BK_KP3;
            static const key_t BK_KP4;
            static const key_t BK_KP5;
            static const key_t BK_KP6;
            static const key_t BK_KP7;
            static const key_t BK_KP8;
            static const key_t BK_KP9;
            static const key_t BK_KP_PERIOD;
            static const key_t BK_KP_DIVIDE;
            static const key_t BK_KP_MULTIPLY;
            static const key_t BK_KP_MINUS;
            static const key_t BK_KP_PLUS;
            static const key_t BK_KP_ENTER;
            static const key_t BK_KP_EQUALS;

            static const key_t BK_UP;
            static const key_t BK_DOWN;
            static const key_t BK_RIGHT;
            static const key_t BK_LEFT;
            static const key_t BK_INSERT;
            static const key_t BK_HOME;
            static const key_t BK_END;
            static const key_t BK_PAGEUP;
            static const key_t BK_PAGEDOWN;

            static const key_t BK_F1;
            static const key_t BK_F2;
            static const key_t BK_F3;
            static const key_t BK_F4;
            static const key_t BK_F5;
            static const key_t BK_F6;
            static const key_t BK_F7;
            static const key_t BK_F8;
            static const key_t BK_F9;
            static const key_t BK_F10;
            static const key_t BK_F11;
            static const key_t BK_F12;
            static const key_t BK_F13;
            static const key_t BK_F14;
            static const key_t BK_F15;

            static const key_t BK_NUMLOCK;
            static const key_t BK_CAPSLOCK;
            static const key_t BK_SCROLLOCK;
            static const key_t BK_RSHIFT;
            static const key_t BK_LSHIFT;
            static const key_t BK_RCTRL;
            static const key_t BK_LCTRL;
            static const key_t BK_RALT;
            static const key_t BK_LALT;
            static const key_t BK_RMET;
            static const key_t BK_LMETA;
            static const key_t BK_LSUPER;
            static const key_t BK_RSUPER;
            static const key_t BK_MODE;
            static const key_t BK_COMPOSE;

            static const key_t BK_HELP;
            static const key_t BK_PRINT;
            static const key_t BK_SYSREQ;
            static const key_t BK_BREAK;
            static const key_t BK_MENU;
            static const key_t BK_POWER;
            static const key_t BK_EURO;
            static const key_t BK_UNDO;

            /*********
                * Mouse *
                *********/
            static const mouse_button_t BM_LEFT;
            static const mouse_button_t BM_RIGHT;
            static const mouse_button_t BM_MIDLE;
            static const mouse_button_t BM_WHEELUP;
            static const mouse_button_t BM_WHEELDOWN;
        public:

            /*!
             * Create window.
             * \param title Window title.
             * \param resolution Screen resolution.
             * \param bpp Bit per pixel.
             * \param fulscreen Fulscreen?
             * \param pc_logger Pointer to logger.
             */
            BAbstractWindow ( const BoxE::Core::BAsciiString &title, const screen_resolution_t &resolution, int bpp, bool fullscreen, BLogger *pc_logger );

            /*!
             * Destructor.
             */
            virtual ~BAbstractWindow();

            /*!
             * Set window titile.
             * \param title Window title.
             */
            virtual void setWindowTitle ( const BoxE::Core::BAsciiString &title );

            /*!
             * Set window resolution.
             */
            virtual void setWindowResolution ( const screen_resolution_t &resolution );

            /*!
             * Is fullscreen activated?
             * \return True if is fullscreen activated, else return false.
             */
            bool isFullscreen() const;

            /*!
             * Get window title.
             * \return Window title.
             */
            BoxE::Core::BAsciiString getWindowTitle() const;

            /*!
             * Get window resolution.
             * \return Window resolution.
             */
            screen_resolution_t getWindowResolution() const;

            /*!
             * Get window bpp.
             * \return Window bpp.
             */
            int getWindowBPP() const;

            /*!
             * Get ....
             */
            virtual unsigned int getTick() const = 0;

            /*!
             * Init window.
             * \return Init status.
             */
            virtual bool init() = 0;

            /*!
             * Show window.
             * \return Show status.
             */
            virtual bool show() = 0;

            /*!
             * Update window.
             * \return Update status.
             */
            virtual bool update() = 0;

            /*!
             * Is key down ?
             * \param key Key.
             * \return Key down?
             */
            virtual bool isKeyDown ( const key_t &key ) const = 0;

            /*!
             * Is key up ?
             * \param key Key.
             * \return Key up?
             */
            virtual bool isKeyUp ( const key_t &key ) const = 0;

            /*!
             * Is mouse button down ?
             * \param button Mouse button.
             * \return Mouse button down?
             */
            virtual bool isMouseButtonDown ( const mouse_button_t &button ) const = 0;

            /*!
             * Is mouse button up?
             * \param button Mouse button.
             * \return Mouse button up?
             */
            virtual bool isMouseButtonUp ( const mouse_button_t &button ) const = 0;

        private:
            BoxE::Core::BAsciiString WindowTitle;
            screen_resolution_t WindowResolutin;
            int                 WindowBPP;
            bool                WindowFullscreen;

        protected:
            BLogger *pcLogger;

            // SIGNALS
        protected:
            BoxE::Core::BSignal0 OnClose;

            BoxE::Core::BSignal2< screen_resolution_t, bool > OnScreenChanged;

            BoxE::Core::BSignal1<key_t> OnKeyUp;
            BoxE::Core::BSignal1<key_t> OnKeyDown;
            BoxE::Core::BSignal1<mouse_button_t> OnMouseUp;
            BoxE::Core::BSignal1<mouse_button_t> OnMouseDown;
            BoxE::Core::BSignal2< int, int > OnMouseMotion;

        public:
            /*!
             * On close signal.
             * \return Signal.
             */
            BoxE::Core::BSignal0 &onClose();

            /*!
             * On screen changed.
             * \return Signal.
             */
            BoxE::Core::BSignal2< screen_resolution_t, bool >& onScreenChanged();

            /*!
             * On key up signal.
             * \return Signal.
             */
            BoxE::Core::BSignal1<key_t>& onKeyUp();

            /*!
             * On key down signal.
             * \return Signal.
             */
            BoxE::Core::BSignal1<key_t>& onKeyDown();


            /*!
             * On mouse button up signal.
             * \return Signal.
             */
            BoxE::Core::BSignal1<mouse_button_t>& onMouseUp();

            /*!
             * On mouse button down signal.
             * \return Signal.
             */
            BoxE::Core::BSignal1<mouse_button_t>& onMouseDown();

            /*!
             * On mouse motion signal.
             * \return Signal.
             */
            BoxE::Core::BSignal2< int, int >& onMouseMotion();

    };

}

#endif // BABSTRACTWINDOW_H
