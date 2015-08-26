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

#ifndef BSDLWINDOW_H
#define BSDLWINDOW_H

#include <BackGenEngine/babstractwindow.h>

#include <SDL/SDL.h>

class BSDLWindow : public BackGenEngine::BAbstractWindow {
    public:
        BSDLWindow ( const BoxE::Core::BAsciiString &title, const screen_resolution_t &resolution, int bpp, bool fullscreen, BackGenEngine::BLogger *pc_logger );
        virtual ~BSDLWindow();

        virtual void setWindowTitle ( const BoxE::Core::BAsciiString &title ) {
            BAbstractWindow::setWindowTitle ( title );
            SDL_WM_SetCaption ( title.constData(), 0 );
        }

        virtual void setWindowResolution ( const BackGenEngine::BAbstractWindow::screen_resolution_t &resolution ) {
            BAbstractWindow::setWindowResolution ( resolution );
            OnScreenChanged.emitSignal ( resolution, isFullscreen() );
        }

        virtual unsigned int getTick() const;

        virtual bool init();
        virtual bool show();
        virtual bool update();

        inline virtual bool isKeyDown ( const key_t &key ) const {
            return aSDLKeyStatus[key];
        }

        inline virtual bool isKeyUp ( const key_t &key ) const {
            return !aSDLKeyStatus[key];
        }

        inline virtual bool isMouseButtonDown ( const mouse_button_t &button ) const {
            return ( SDL_GetMouseState ( 0, 0 ) & SDL_BUTTON ( button ) );
        }

        inline virtual bool isMouseButtonUp ( const mouse_button_t &button ) const {
            return ! ( SDL_GetMouseState ( 0, 0 ) & SDL_BUTTON ( button ) );
        }

    private:
        const SDL_VideoInfo *pSDLVideoInfo;
        int SDLFlags;
        SDL_Surface *pSDLScreen;
        SDL_Event SDLEvent;
        unsigned char *aSDLKeyStatus; //!< SDL key status.
        bool NeedClose;
};

#endif // BSDLWINDOW_H
