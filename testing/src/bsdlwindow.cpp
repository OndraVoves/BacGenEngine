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

#include "bsdlwindow.h"

#include <BackGenEngine/blogger.h>

/***************
 * Keys define *
 ***************/
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_UNKNOWN = SDLK_UNKNOWN;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_BACKSPACE = SDLK_BACKSPACE;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_TAB = SDLK_TAB;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_CLEAR = SDLK_CLEAR;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_RETURN = SDLK_RETURN;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_PAUSE = SDLK_PAUSE;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_ESCAPE = SDLK_ESCAPE;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_SPACE = SDLK_SPACE;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_EXCLAIM = SDLK_EXCLAIM;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_QUOTEDBL = SDLK_QUOTEDBL;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_HASH = SDLK_HASH;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_DOLLAR = SDLK_DOLLAR;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_AMPERSAND = SDLK_AMPERSAND;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_QUOTE = SDLK_QUOTE;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_LEFTPAREN = SDLK_LEFTPAREN;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_RIGHTPARE = SDLK_RIGHTPAREN;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_ASTERISK = SDLK_ASTERISK;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_PLUS = SDLK_PLUS;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_COMMA = SDLK_COMMA;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_MINUS = SDLK_MINUS;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_PERIOD = SDLK_PERIOD;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_SLASH = SDLK_SLASH;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_0 = SDLK_0;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_1 = SDLK_1;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_2 = SDLK_2;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_3 = SDLK_3;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_4 = SDLK_4;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_5 = SDLK_5;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_6 = SDLK_6;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_7 = SDLK_7;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_8 = SDLK_8;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_9 = SDLK_9;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_COLON = SDLK_COLON;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_SEMICOLON = SDLK_SEMICOLON;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_LESS = SDLK_LESS;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_EQUALS = SDLK_EQUALS;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_GREATER = SDLK_GREATER;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_QUESTION = SDLK_QUESTION;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_AT = SDLK_AT;

const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_LEFTBRACKET = SDLK_LEFTBRACKET;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_BACKSLASH = SDLK_BACKSLASH;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_RIGHTBRACKET = SDLK_RIGHTBRACKET;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_CARET = SDLK_CARET;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_UNDERSCORE = SDLK_UNDERSCORE;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_BACKQUOTE = SDLK_BACKQUOTE;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_a = SDLK_a;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_b = SDLK_b;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_c = SDLK_c;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_d = SDLK_d;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_e = SDLK_e;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_f = SDLK_f;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_g = SDLK_g;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_h = SDLK_h;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_i = SDLK_i;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_j = SDLK_j;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_k = SDLK_k;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_l = SDLK_l;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_m = SDLK_m;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_n = SDLK_n;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_o = SDLK_o;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_p = SDLK_p;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_q = SDLK_q;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_r = SDLK_r;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_s = SDLK_s;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_t = SDLK_t;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_u = SDLK_u;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_v = SDLK_v;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_w = SDLK_w;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_x = SDLK_x;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_y = SDLK_y;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_z = SDLK_z;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_DELETE = SDLK_DELETE;

const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_KP0 = SDLK_KP0;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_KP1 = SDLK_KP1;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_KP2 = SDLK_KP2;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_KP3 = SDLK_KP3;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_KP4 = SDLK_KP4;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_KP5 = SDLK_KP5;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_KP6 = SDLK_KP6;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_KP7 = SDLK_KP7;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_KP8 = SDLK_KP8;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_KP9 = SDLK_KP9;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_KP_PERIOD = SDLK_KP_PERIOD;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_KP_DIVIDE = SDLK_KP_DIVIDE;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_KP_MULTIPLY = SDLK_KP_MULTIPLY;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_KP_MINUS = SDLK_KP_MINUS;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_KP_PLUS = SDLK_KP_PLUS;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_KP_ENTER = SDLK_KP_ENTER;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_KP_EQUALS = SDLK_KP_EQUALS;

const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_UP = SDLK_UP;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_DOWN = SDLK_DOWN;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_RIGHT = SDLK_RIGHT;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_LEFT = SDLK_LEFT;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_INSERT = SDLK_INSERT;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_HOME = SDLK_HOME;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_END = SDLK_END;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_PAGEUP = SDLK_PAGEUP;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_PAGEDOWN = SDLK_PAGEDOWN;

const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_F1 = SDLK_F1;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_F2 = SDLK_F2;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_F3 = SDLK_F3;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_F4 = SDLK_F4;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_F5 = SDLK_F5;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_F6 = SDLK_F6;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_F7 = SDLK_F7;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_F8 = SDLK_F8;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_F9 = SDLK_F9;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_F10 = SDLK_F10;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_F11 = SDLK_F11;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_F12 = SDLK_F12;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_F13 = SDLK_F13;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_F14 = SDLK_F14;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_F15 = SDLK_F15;

const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_NUMLOCK = SDLK_NUMLOCK;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_CAPSLOCK = SDLK_CAPSLOCK;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_SCROLLOCK = SDLK_SCROLLOCK;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_RSHIFT = SDLK_RSHIFT;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_LSHIFT = SDLK_LSHIFT;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_RCTRL = SDLK_RCTRL;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_LCTRL = SDLK_LCTRL;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_RALT = SDLK_RALT;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_LALT = SDLK_LALT;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_RMET = SDLK_RMETA;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_LMETA = SDLK_LMETA;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_LSUPER = SDLK_LSUPER;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_RSUPER = SDLK_RSUPER;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_MODE = SDLK_MODE;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_COMPOSE = SDLK_COMPOSE;

const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_HELP = SDLK_HELP;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_PRINT = SDLK_PRINT;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_SYSREQ = SDLK_SYSREQ;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_BREAK = SDLK_BREAK;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_MENU = SDLK_MENU;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_POWER = SDLK_POWER;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_EURO = SDLK_EURO;
const BackGenEngine::BAbstractWindow::key_t BackGenEngine::BAbstractWindow::BK_UNDO = SDLK_UNDO;

/*********
    * Mouse *
    *********/
const BackGenEngine::BAbstractWindow::mouse_button_t BackGenEngine::BAbstractWindow::BM_LEFT = 1;
const BackGenEngine::BAbstractWindow::mouse_button_t BackGenEngine::BAbstractWindow::BM_RIGHT = 3;
const BackGenEngine::BAbstractWindow::mouse_button_t BackGenEngine::BAbstractWindow::BM_MIDLE = 2;
const BackGenEngine::BAbstractWindow::mouse_button_t BackGenEngine::BAbstractWindow::BM_WHEELUP = 4;
const BackGenEngine::BAbstractWindow::mouse_button_t BackGenEngine::BAbstractWindow::BM_WHEELDOWN = 5;

BSDLWindow::BSDLWindow ( const BoxE::Core::BAsciiString &title, const screen_resolution_t &resolution, int bpp, bool fullscreen,  BackGenEngine::BLogger *pc_logger )
    : BAbstractWindow ( title, resolution, bpp, fullscreen, pc_logger  ), SDLFlags ( 0 ), NeedClose ( true )  {
}

BSDLWindow::~BSDLWindow() {
}

unsigned int BSDLWindow::getTick() const {
    return SDL_GetTicks();
}

bool BSDLWindow::init() {
    if ( SDL_Init ( SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE ) < 0 ) {
        pcLogger->error ( BoxE::Core::BAsciiString ( "Could not init SDL: " ).append ( SDL_GetError() ) );
        return false;
    }

    SDL_EnableUNICODE ( true );

    //pcLogger->debug ( "SDL init -> OK" );
    return true;
}

bool BSDLWindow::show() {
    pSDLVideoInfo = SDL_GetVideoInfo();

    SDLFlags |= SDL_OPENGL;

    if ( isFullscreen() ) {
        SDLFlags |= SDL_FULLSCREEN;
    }

    /*SDLFlags |= SDL_HWPALETTE;

    if ( pSDLVideoInfo->hw_available ) {
        SDLFlags |= SDL_HWSURFACE;
    } else {
        SDLFlags |= SDL_SWSURFACE;
    }

            if ( pSDLVideoInfo->blit_hw ) {
    SDLFlags |= SDL_HWACCEL;
    }*/

    pSDLScreen = SDL_SetVideoMode ( BAbstractWindow::getWindowResolution().x(), BAbstractWindow::getWindowResolution().y(), getWindowBPP(), SDLFlags );

    switch ( getWindowBPP() ) {
        case 16:
            SDL_GL_SetAttribute ( SDL_GL_RED_SIZE, 4 );
            SDL_GL_SetAttribute ( SDL_GL_GREEN_SIZE, 4 );
            SDL_GL_SetAttribute ( SDL_GL_BLUE_SIZE, 4 );
            SDL_GL_SetAttribute ( SDL_GL_ALPHA_SIZE, 4 );
            break;
        case 32:
            SDL_GL_SetAttribute ( SDL_GL_RED_SIZE, 8 );
            SDL_GL_SetAttribute ( SDL_GL_GREEN_SIZE, 8 );
            SDL_GL_SetAttribute ( SDL_GL_BLUE_SIZE, 8 );
            SDL_GL_SetAttribute ( SDL_GL_ALPHA_SIZE, 8 );
            break;
    }

    SDL_GL_SetAttribute ( SDL_GL_DOUBLEBUFFER, 1 );
    SDL_GL_SetAttribute ( SDL_GL_DEPTH_SIZE, 24 );
    //SDL_GL_SetAttribute ( SDL_GL_ACCELERATED_VISUAL, 1 );
    //SDL_GL_SetAttribute ( SDL_GL_SWAP_CONTROL, 1 );

    SDL_WM_SetCaption ( BackGenEngine::BAbstractWindow::getWindowTitle().constData(), 0 );

    if ( !pSDLScreen ) {
        pcLogger->error ( BoxE::Core::BAsciiString ( "Could not set video mode: " ).append ( SDL_GetError() ) );
        return false;
    }


    aSDLKeyStatus = SDL_GetKeyState ( 0 );


    NeedClose = false;

    return true;
}

bool BSDLWindow::update() {
    while ( SDL_PollEvent ( &SDLEvent ) ) {
        switch ( SDLEvent.type ) {
            case SDL_KEYDOWN:
                OnKeyDown.emitSignal ( SDLEvent.key.keysym.sym );
                break;

            case SDL_KEYUP:
                OnKeyUp.emitSignal ( SDLEvent.key.keysym.sym );
                break;

            case SDL_MOUSEBUTTONDOWN:
                OnMouseDown.emitSignal ( SDLEvent.button.button );
                break;

            case SDL_MOUSEBUTTONUP:
                OnMouseUp.emitSignal ( SDLEvent.button.button );
                break;

            case SDL_MOUSEMOTION:
                OnMouseMotion.emitSignal ( SDLEvent.motion.x, SDLEvent.motion.y );
                break;

            case SDL_QUIT:
                NeedClose = true;
                OnClose.emitSignal();
                break;

            default:
                break;
        }
    }
    return NeedClose;
}


