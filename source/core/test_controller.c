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
#include "extra_math.h"
#include "list.h"
#include "entity.h"
#include "sprite.h"
#include "physics.h"
#include "graphics.h"

Entity* ship;
Entity* flames;
Entity* yoshi;
Entity* bolt;
Entity* tmp;
List*   bolts;

unsigned char flags = 0;

#define INITIALISED 1
#define CONTINUE    2
#define UPDATE      4
#define DRAW        8
#define ENGINE      16

#define FLAME_OFFSET_X 


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

    bolt = NewEntity("source/entities/bolt.entity");

    ship->center_x          = 120;
    ship->center_y          = 120;
    ship->sprite->z_index   = 5;

    yoshi->center_x         = 220;
    yoshi->center_y         = 120;
    yoshi->a_speed          = 2;
    yoshi->x_speed          = 1;
    yoshi->y_speed          = 1;
    yoshi->sprite->z_index  = 4;

    bolt->sprite->z_index   = 1;

    bolts = NewList();

    flags = (INITIALISED | CONTINUE | UPDATE | DRAW);
    return 0;
}

ERR ExitTestController()
{
    FreeEntity(ship);
    FreeEntity(flames);
    FreeEntity(yoshi);
    int i;
    for(i = 0; i < bolts->size; i++)
        FreeEntity((Entity*)GetValue(bolts, i));
    ClearList(bolts);
    FreeEntity(bolt);

    return 0;
}

ERR TestControllerLoop()
{
    while(flags & CONTINUE)
    {
        //AddForce(ship->physics_object, 0.0, 10.0, ship->physics_object->cog_x, ship->physics_object->cog_y);        

        SDL_Event event;
        while(SDL_PollEvent(&event) != 0)
        {
            if(event.type == SDL_QUIT)
                 flags ^= CONTINUE;
            else if(event.type == SDL_KEYDOWN && event.key.repeat == 0)
                switch(event.key.keysym.sym)
                {
                case SDLK_UP: 
                    flames->sprite->data[CURRENT_LOOP] ^= 1;
                    flags ^= ENGINE;
                    break;
                case SDLK_DOWN:
                    ship->y_speed = 0.0;
                    ship->x_speed = 0.0;
                    break;
                case SDLK_LEFT: ship->a_speed   = -5.0; break;
                case SDLK_RIGHT: ship->a_speed  = 5.0; break;
                case SDLK_SPACE:
                    tmp = CopyEntity(bolt);
                    tmp->center_x = ship->center_x;
                    tmp->center_y = ship->center_y;
                    tmp->angle = ship->angle;
                    tmp->x_speed = RotateOffsetX(0.0, -10.0, ship->angle);
                    tmp->y_speed = RotateOffsetY(0.0, -10.0, ship->angle);
                    InsertValue(tmp, bolts, 0);
                    break;
                }
            else if(event.type == SDL_KEYUP)
                switch(event.key.keysym.sym)
                {
                case SDLK_UP:
                    flames->sprite->data[CURRENT_LOOP] ^= 1;
                    flags ^= ENGINE;
                    break;
                case SDLK_DOWN: break;
                case SDLK_LEFT: ship->a_speed   = 0.0; break;
                case SDLK_RIGHT: ship->a_speed  = 0.0; break;
                case SDLK_SPACE: 
                    break;
                }
        }

        if(flags & UPDATE)
        {
            if(flags & ENGINE)
                AddForce(ship->physics_object, RotateOffsetX(0.0, -20.0, ship->angle), RotateOffsetY(0.0, -20.0, ship->angle),
                        ship->physics_object->cog_x, ship->physics_object->cog_y);
            UpdateEntity(ship);

            flames->angle = ship->angle;
            flames->center_x = ship->center_x + RotateOffsetX(0.0, ship->sprite->h * ship->sprite->zoom, ship->angle);
            flames->center_y = ship->center_y + RotateOffsetY(0.0, ship->sprite->h * ship->sprite->zoom, ship->angle);
            UpdateEntity(flames);

            UpdateEntity(yoshi);
            yoshi->sprite->zoom      += 0.01;

            int i;
            for(i = 0; i < bolts->size; i++)
                UpdateEntity((Entity*)GetValue(bolts, i));

        }

        if(flags & DRAW)
        {
            DrawEntity(ship);
            DrawEntity(flames);
            DrawEntity(yoshi);
            int i;
            for(i = 0; i < bolts->size; i++)
                DrawEntity((Entity*)GetValue(bolts, i));
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
