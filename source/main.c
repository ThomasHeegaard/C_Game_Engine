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
#include "utils/sdl_wrapper.h"
#include "graphics/fps_manager.h"
#include "graphics/sprite.h"

#include <SDL2/SDL.h>

int main()
{
    if(InitSDL() != 0)
        return 1;
    InitFPS();

    Sprite* test = NewSprite(0, ANIMATION);
    if(test == NULL)
    {
        fprintf(stderr, "FAIL");
        return 1;
    }

    test->w         = 64;
    test->h         = 64;
    test->center_x  = 120;
    test->center_y  = 120;
    test->zoom      = 1.0;
    test->flags |= PLAY;

    test->data[FRAMES]          = 8;
    test->data[TARGET_FPS]      = 15;

    Sprite* test2 = NewSprite(0, ANIMATION);
    if(test2 == NULL)
    {
        fprintf(stderr, "FAIL");
        return 1;
    }

    test2->w         = 64;
    test2->h         = 64;
    test2->center_x  = 220;
    test2->center_y  = 120;
    test2->zoom      = 1.0;
    test2->flags |= PLAY;

    test2->data[FRAMES]          = 8;
    test2->data[TARGET_FPS]      = 25;

    int i;

    for(i = 200; i > 0; i--)
    {
        ClearScreen();
        if(DrawSprite(test) != 0) printf("ERROR");
        if(DrawSprite(test2) != 0) printf("ERROR");
        UpdateScreen();
        test->center_x  += 1;
        test->center_y  += 1;
        test->angle     += 2.0;
        test->zoom      += 0.01;
        ManageFPS();
    }

    printf("FPS: %d\n", GetFPS());

    FreeSprite(test);
    FreeSprite(test2);
    ExitSDL();
    return 0;
}
