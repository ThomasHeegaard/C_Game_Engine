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
    test->zoom      = 1.0;

    test->data[FRAMES]          = 8;
    test->data[TARGET_FPS]      = 15;

    int i;

    for(i = 200; i > 0; i--)
    {
        ClearScreen();
        DrawSprite(test);
        UpdateScreen();
        test->center_x  += 1;
        test->center_y  += 1;
        test->angle     += 2.0;
        test->zoom      += 0.01;
        if(i < 100)
            test->flags |= PLAY;
        ManageFPS();
    }

    printf("FPS: %d\n", GetFPS());

    FreeSprite(test);
    ExitSDL();
    return 0;
}
