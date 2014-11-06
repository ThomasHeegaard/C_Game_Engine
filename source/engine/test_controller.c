/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : test_controller.c
|Author   : Thomas Heegaard
|Created  : 11/06/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#include "test_controller.h"

#include <stdlib.h>
#include <stdio.h>
#include "../utils/sdl_wrapper.h"
#include "../graphics/fps_manager.h"
#include "../graphics/sprite.h"

Sprite* test;
Sprite* test2;

unsigned char flags = 0;

#define INITIALISED 1
#define CONTINUE    2


ERR InitTestController()
{
    test = NewSprite(0, ANIMATION);
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

    test2 = NewSprite(0, ANIMATION);
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

    flags = (INITIALISED | CONTINUE);
    return 0;
}

ERR ExitTestController()
{
    FreeSprite(test);
    FreeSprite(test2);
    return 0;
}

ERR TestControllerLoop()
{
    while(flags & CONTINUE)
    {
        ClearScreen();
        SDL_Event event;
        while(SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
                 flags ^= CONTINUE;
            else if(event.type == SDL_KEYDOWN)
                switch(event.key.keysym.sym)
                {
                case SDLK_UP: test2->center_y -= 5; break;
                case SDLK_DOWN: test2->center_y += 5; break;
                case SDLK_LEFT: test2->center_x -= 5; break;
                case SDLK_RIGHT: test2->center_x += 5; break;
                }
        }
        test->center_x  += 1;
        test->center_y  += 1;
        test->angle     += 2.0;
        test->zoom      += 0.01;
        DrawSprite(test);
        DrawSprite(test2);
        UpdateScreen();
        ManageFPS();
    }
    return ExitTestController();
}

ERR StartTestController()
{
    if(flags & INITIALISED)
        return TestControllerLoop();
    
    if(InitTestController() == 0)
        return TestControllerLoop();
    
    return 1;
}
