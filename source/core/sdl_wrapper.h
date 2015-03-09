/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : sdl_wrapper.h
|Author   : Thomas Heegaard
|Created  : 10/28/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#ifndef SDL_WRAPPER_H
#define SDL_WRAPPER_H

#include "global_defines.h"
#include <SDL2/SDL.h>

//======================================================================================
//                  DATA
//======================================================================================

typedef struct Screen
{
    SDL_Window*     window;
    SDL_Renderer*   renderer;
} Screen;

typedef struct PixelMap
{
    SDL_Texture*    texture;
    int             w;
    int             h;
    Vector          pos;
    unsigned short  z_index;
    Uint32*         pixels;
}
PixelMap;

extern SDL_Texture** texture_bank;

//======================================================================================
//                  DEFINITIONS
//======================================================================================

#define RECT        SDL_Rect

#define TRANSP_R    255
#define TRANSP_G    0
#define TRANSP_B    255

//======================================================================================
//                  FUNCTIONS
//======================================================================================
ERR InitSDL();

//======================================================================================
ERR LoadTexture(unsigned short texture_id);

//======================================================================================
ERR DrawTexture(unsigned short texture_id, float angle, 
                SDL_Rect* src_rect, SDL_Rect* dst_rect);

//======================================================================================
void FreeTexture(unsigned short texture_id);

PixelMap* NewPixelMap(int w, int h, Vector pos, unsigned short z_index);

ERR RenderPixelMap(PixelMap* pm);

void FreePixelMap(PixelMap* pm);

//======================================================================================
ERR ClearScreen();

//======================================================================================
ERR UpdateScreen();

//======================================================================================
ERR ExitSDL();

#endif //SDL_WRAPPER_H
