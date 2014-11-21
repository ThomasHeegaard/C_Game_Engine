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
#include "entity.h"
#include "../graphics/sprite.h"
#include "../graphics/graphics.h"

Entity* test;
Entity* test2;

unsigned char flags = 0;

#define INITIALISED 1
#define CONTINUE    2
#define UPDATE      4
#define DRAW        8


ERR InitTestController()
{
    test = NewEntity("source/entities/ship.entity");
    if(test == NULL)
        return 1;
    test2 = NewEntity("source/entities/test.entity");
    if(test2 == NULL)
    {
        free(test);
        return 1;
    }

    test->center_x          = 120;
    test->center_y          = 120;

    test2->center_x         = 220;
    test2->center_y         = 120;
    test2->angular_speed    = 2;
    test2->x_speed          = 1;
    test2->y_speed          = 1;
    test2->sprite->z_index  = 4;


    flags = (INITIALISED | CONTINUE | UPDATE | DRAW);
    return 0;
}

ERR ExitTestController()
{
    FreeEntity(test);
    FreeEntity(test2);
    return 0;
}

ERR TestControllerLoop()
{
    while(flags & CONTINUE)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
                 flags ^= CONTINUE;
            else if(event.type == SDL_KEYDOWN)
                switch(event.key.keysym.sym)
                {
                case SDLK_UP: test->y_speed     = -5.0; break;
                case SDLK_DOWN: test->y_speed   = 5.0; break;
                case SDLK_LEFT: test->x_speed   = -5.0; break;
                case SDLK_RIGHT: test->x_speed  = 5.0; break;
                case SDLK_SPACE: test->sprite->data[CURRENT_LOOP] ^= 1;
                }
            else if(event.type == SDL_KEYUP)
                switch(event.key.keysym.sym)
                {
                case SDLK_UP: test->y_speed     = 0.0; break;
                case SDLK_DOWN: test->y_speed   = 0.0; break;
                case SDLK_LEFT: test->x_speed   = 0.0; break;
                case SDLK_RIGHT: test->x_speed  = 0.0; break;
                }
        }

        if(flags & UPDATE)
        {
            UpdateEntity(test);
            UpdateEntity(test2);
            test2->sprite->zoom      += 0.01;
        }

        if(flags & DRAW)
        {
            DrawEntity(test);
            DrawEntity(test2);
            Render();
        }
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
