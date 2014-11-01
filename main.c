/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : main.c
|Author   : Thomas Heegaard
|Created  : 10/30/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/


#include <stdlib.h>
#include <stdio.h>
#include "sdl_wrapper.h"
#include "sprite.h"

#include <SDL2/SDL.h>

int main()
{
    if(InitSDL() != 0)
        return 1;

    Sprite* test = NewSprite(0, ANIMATION | OSCILLATING);
    if(test == NULL)
    {
        fprintf(stderr, "FAIL");
        return 1;
    }

    test->w         = 64;
    test->h         = 64;
    test->center_x  = 120;
    test->center_y  = 120;
    test->angle     = 0;
    test->zoom      = 3.0;

    test->data[CURRENT_FRAME]   = 0;
    test->data[FRAMES]          = 8;

    int i;

    for(i = 200; i > 0; i--)
    {
        ClearScreen();
        DrawSprite(test);
        UpdateScreen();
        test->center_x += 1;
        test->center_y += 1;
        test->angle += 2.0;
        if(i < 100)
            test->flags |= PLAY;
        SDL_Delay(2);
    }

    FreeSprite(test);
    ExitSDL();
    return 0;
}
