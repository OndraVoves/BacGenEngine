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

#include "../include/babstractwindow.h"

namespace BackGenEngine {
    BAbstractWindow::BAbstractWindow ( const BoxE::Core::BAsciiString &title, const screen_resolution_t &resolution, int bpp, bool fullscreen, BLogger *pc_logger ) : WindowTitle ( title ), WindowResolutin ( resolution ), WindowBPP ( bpp ), WindowFullscreen ( fullscreen ), pcLogger ( pc_logger )  {
    };


    BAbstractWindow::~BAbstractWindow() {
    }

    void BAbstractWindow::setWindowTitle ( const BoxE::Core::BAsciiString &title ) {
        WindowTitle = title;
    }

    void BAbstractWindow::setWindowResolution ( const screen_resolution_t &resolution ) {
        WindowResolutin = resolution;
    }


    bool BAbstractWindow::isFullscreen() const {
        return WindowFullscreen;
    }

    BoxE::Core::BAsciiString BAbstractWindow::getWindowTitle() const {
        return WindowTitle;
    }


    BAbstractWindow::screen_resolution_t BAbstractWindow::getWindowResolution() const {
        return WindowResolutin;
    }

    int BAbstractWindow::getWindowBPP() const {
        return WindowBPP;
    }

    BoxE::Core::BSignal0 &BAbstractWindow::onClose() {
        return OnClose;
    }

    BoxE::Core::BSignal2< BAbstractWindow::screen_resolution_t, bool >& BAbstractWindow::onScreenChanged() {
        return OnScreenChanged;
    }

    BoxE::Core::BSignal1<BAbstractWindow::key_t>& BAbstractWindow::onKeyUp() {
        return OnKeyUp;
    }

    BoxE::Core::BSignal1<BAbstractWindow::key_t>& BAbstractWindow::onKeyDown() {
        return OnKeyDown;
    }

    BoxE::Core::BSignal1<BAbstractWindow::mouse_button_t>& BAbstractWindow::onMouseUp() {
        return OnMouseUp;
    }

    BoxE::Core::BSignal1<BAbstractWindow::mouse_button_t>& BAbstractWindow::onMouseDown() {
        return OnMouseDown;
    }

    BoxE::Core::BSignal2< int, int >& BAbstractWindow::onMouseMotion() {
        return OnMouseMotion;
    }
}