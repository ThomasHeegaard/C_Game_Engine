/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : sdl_wrapper.c
|Author   : Thomas Heegaard
|Created  : 10/26/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#include "sdl_wrapper.h"
#include "../engine/input.h"
#include "../graphics/texture_bank.h"



const char*     texture_filenames[TEXTURE_COUNT]    = {TEXTURE_FILENAMES};
SDL_Texture**   texture_bank                        = NULL;
Screen*         screen                              = NULL;


ERR InitSDL()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "SDL initiaisation failed: %s\n", SDL_GetError());
        return 1;
    }

    texture_bank = (SDL_Texture**)malloc(TEXTURE_COUNT * sizeof(SDL_Texture*));
    if(texture_bank == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for texture array\n");
        return 1;
    }
    int i; 
    for(i = 0; i < TEXTURE_COUNT; i++)
        texture_bank[i] = NULL;

    screen = (Screen*)malloc(sizeof(Screen));
    if(screen == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for screen structure\n");
        return 1;
    }

    screen->window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    if(screen->window == NULL)
    {
        fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        return 1;
    }

    screen->renderer = SDL_CreateRenderer(screen->window, -1, SDL_RENDERER_SOFTWARE);
    if(screen->renderer == NULL)
    {
        fprintf(stderr, "Renderer creation failed: %s\n", SDL_GetError());
        return 1;
    }

    return 0;   
}

ERR LoadTexture(unsigned short texture_id)
{
    if(screen == NULL)
    {
        fprintf(stderr, "Screen not found\n");
        return 1;
    }
    if(texture_bank[texture_id] != NULL)
    {
        fprintf(stderr, "Texture %d allready loaded\n", texture_id);
        return 0;
    }

    SDL_Surface* tmp = SDL_LoadBMP(texture_filenames[texture_id]);
    if(tmp == NULL)
    {
        fprintf(stderr, "Error creating surface for texture %d : %s\n", texture_id, SDL_GetError());
        return 1;
    }

    SDL_SetColorKey(tmp, SDL_TRUE, SDL_MapRGB(tmp->format, TRANSP_R, TRANSP_G, TRANSP_B));

    texture_bank[texture_id] = SDL_CreateTextureFromSurface(screen->renderer, tmp);
    SDL_FreeSurface(tmp);
    if(texture_bank[texture_id] == NULL)
    {
        fprintf(stderr, "Error creating texture from surface for %d : %s\n", texture_id, SDL_GetError());
        return 1;
    }
    
    return 0;
}

ERR DrawTexture(unsigned short texture_id, float angle, 
                SDL_Rect* src_rect, SDL_Rect* dst_rect)
{
    if(screen == NULL)
    {
        fprintf(stderr, "Screen not found\n");
        return 1;
    }
    if(texture_bank[texture_id] == NULL)
    {
        fprintf(stderr, "Texture not loaded\n");
        return 1;
    }
    
    if(SDL_RenderCopyEx(screen->renderer, texture_bank[texture_id], 
                            src_rect, dst_rect, angle, NULL, SDL_FLIP_NONE) != 0)
    {
        fprintf(stderr, "Error rendering texture : %s\n", SDL_GetError());
        return 1;
    }
    return 0;
}

void FreeTexture(unsigned short texture_id)
{
    if(texture_bank == NULL)
        return;
    if(texture_bank[texture_id] == NULL)
        return;
    SDL_DestroyTexture(texture_bank[texture_id]);
    texture_bank[texture_id] = NULL;
}

ERR ClearScreen()
{
    if(screen == NULL)
        return 1;
    if(screen->renderer == NULL)
        return 1;

    SDL_RenderClear(screen->renderer);
    return 0;
}

ERR UpdateScreen()
{
    if(screen == NULL)
        return 1;
    if(screen->renderer == NULL)
        return 1;

    SDL_RenderPresent(screen->renderer);
    return 0;
}

void HandleEvent(SDL_Event* event) 
{
/*
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
*/
}

ERR HandleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
        HandleEvent(&event);
    return 0;
}

ERR ExitSDL()
{
    if(texture_bank != NULL)
    {
        int i;
        for(i = 0; i < TEXTURE_COUNT; i++)
            FreeTexture(i);
        free(texture_bank);
    }

    if(screen != NULL)
    {
        SDL_DestroyRenderer(screen->renderer);
        SDL_DestroyWindow(screen->window);
        free(screen);
    }

    SDL_Quit();
    return 0;
}
