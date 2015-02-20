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
#include "sdl_wrapper.h"
#include "entity.h"
#include "sprite.h"
#include "graphics.h"

Entity* ship;
Entity* flames;
Entity* yoshi;

unsigned char flags = 0;

#define INITIALISED 1
#define CONTINUE    2
#define UPDATE      4
#define DRAW        8


ERR InitTestController()
{
    ship = NewEntity("source/entities/ship.entity");
    if(ship == NULL)
        return 1;
    flames = NewEntity("source/entities/flames.entity");
    if(flames == NULL)
    {
        FreeEntity(ship);
        return 1;
    }
    yoshi = NewEntity("source/entities/test.entity");
    if(yoshi == NULL)
    {
        FreeEntity(ship);
        FreeEntity(flames);
        return 1;
    }

    ship->center_x          = 120;
    ship->center_y          = 120;

    yoshi->center_x         = 220;
    yoshi->center_y         = 120;
    yoshi->angular_speed    = 2;
    yoshi->x_speed          = 1;
    yoshi->y_speed          = 1;
    yoshi->sprite->z_index  = 4;


    flags = (INITIALISED | CONTINUE | UPDATE | DRAW);
    return 0;
}

ERR ExitTestController()
{
    FreeEntity(ship);
    FreeEntity(flames);
    FreeEntity(yoshi);
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
                case SDLK_UP: ship->y_speed     = -5.0; break;
                case SDLK_DOWN: ship->y_speed   = 5.0; break;
                case SDLK_LEFT: ship->x_speed   = -5.0; break;
                case SDLK_RIGHT: ship->x_speed  = 5.0; break;
                case SDLK_SPACE: flames->sprite->data[CURRENT_LOOP] ^= 1; break;
                }
            else if(event.type == SDL_KEYUP)
                switch(event.key.keysym.sym)
                {
                case SDLK_UP: ship->y_speed     = 0.0; break;
                case SDLK_DOWN: ship->y_speed   = 0.0; break;
                case SDLK_LEFT: ship->x_speed   = 0.0; break;
                case SDLK_RIGHT: ship->x_speed  = 0.0; break;
                }
        }

        if(flags & UPDATE)
        {
            UpdateEntity(ship);
            flames->center_x = ship->center_x;
            flames->center_y = ship->center_y + ship->sprite->h * ship->sprite->zoom;
            UpdateEntity(flames);
            UpdateEntity(yoshi);
            yoshi->sprite->zoom      += 0.01;
        }

        if(flags & DRAW)
        {
            DrawEntity(ship);
            DrawEntity(flames);
            DrawEntity(yoshi);
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
