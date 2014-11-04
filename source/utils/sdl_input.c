/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : sdl_input.c
|Author   : Thomas Heegaard
|Created  : 11/04/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#include "sdl_input.h"
#include "../engine/input.h"

void HandleEvent(SDL_Event* event) 
{
    switch(event->type) 
    {
    case SDL_ACTIVEEVENT:
    {
        switch(event->active.state) 
        {
        case SDL_APPMOUSEFOCUS:
        {
            if ( event->active.gain )
                MouseFocus();
            else
                MouseBlur();
            break;
        }
        case SDL_APPINPUTFOCUS:
        {
            if ( event->active.gain )
                InputFocus();
            else
                InputBlur();
            break;
        }
        case SDL_APPACTIVE:
        {
            if ( event->active.gain )
                Restore();
            else
                Minimize();
            break;
        }
        }
        break;
    }

    case SDL_KEYDOWN:
    {
        KeyDown(event->key.keysym.sym,event->key.keysym.mod,event->key.keysym.unicode);
        break;
    }

    case SDL_KEYUP:
    {
        KeyUp(event->key.keysym.sym,event->key.keysym.mod,event->key.keysym.unicode);
        break;
    }

    case SDL_MOUSEMOTION:
    {
        MouseMove(event->motion.x,event->motion.y,event->motion.xrel,event->motion.yrel,(event->motion.state&SDL_BUTTON(SDL_BUTTON_LEFT))!=0,(event->motion.state&SDL_BUTTON(SDL_BUTTON_RIGHT))!=0,(event->motion.state&SDL_BUTTON(SDL_BUTTON_MIDDLE))!=0);
        break;
    }

    case SDL_MOUSEBUTTONDOWN:
    {
        switch(event->button.button) 
        {
        case SDL_BUTTON_LEFT: 
        {
            LButtonDown(event->button.x,event->button.y);
            break;
        }
        case SDL_BUTTON_RIGHT:
        {
            RButtonDown(event->button.x,event->button.y);
            break;
        }
        case SDL_BUTTON_MIDDLE:
        {
            MButtonDown(event->button.x,event->button.y);
            break;
        }
        }
        break;
    }

    case SDL_MOUSEBUTTONUP:    
    {
        switch(event->button.button) 
        {
        case SDL_BUTTON_LEFT: 
        {
            LButtonUp(event->button.x,event->button.y);
            break;
        }
        case SDL_BUTTON_RIGHT:
        {
            RButtonUp(event->button.x,event->button.y);
            break;
        }
        case SDL_BUTTON_MIDDLE:
        {
            MButtonUp(event->button.x,event->button.y);
            break;
        }
        }
        break;
    }

    case SDL_JOYAXISMOTION: 
    {
        JoyAxis(event->jaxis.which,event->jaxis.axis,event->jaxis.value);
        break;
    }

    case SDL_JOYBALLMOTION: 
    {
        JoyBall(event->jball.which,event->jball.ball,event->jball.xrel,event->jball.yrel);
        break;
    }

    case SDL_JOYHATMOTION: 
    {
        JoyHat(event->jhat.which,event->jhat.hat,event->jhat.value);
        break;
    }
    case SDL_JOYBUTTONDOWN: 
    {
        JoyButtonDown(event->jbutton.which,event->jbutton.button);
        break;
    }

    case SDL_JOYBUTTONUP: 
    {
        JoyButtonUp(event->jbutton.which,event->jbutton.button);
        break;
    }

    case SDL_QUIT: 
    {
        Exit();
        break;
    }

    case SDL_SYSWMEVENT: 
    {
        //Ignore
        break;
    }

    case SDL_VIDEORESIZE: 
    {
        Resize(event->resize.w,event->resize.h);
        break;
    }

    case SDL_VIDEOEXPOSE: 
    {
        Expose();
        break;
    }

    default: 
    {
        User(event->user.type,event->user.code,event->user.data1,event->user.data2);
        break;
    }
    }
}
