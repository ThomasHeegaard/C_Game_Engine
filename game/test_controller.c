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
#include "draw.h"
#include "debug.h"

Entity* ship;
Entity* flames;
Entity* yoshi;
Entity* bolt;
Entity* tmp;
List*   bolts;
PixelMap* visual_debug;

unsigned char flags = 0;

#define INITIALISED 1
#define CONTINUE    2
#define UPDATE      4
#define DRAW        8
#define ENGINE      16


ERR InitTestController()
{
    ship = NewEntity("game/entities/ship.entity");
    if(ship == NULL)
        return 1;
    flames = NewEntity("game/entities/flames.entity");
    if(flames == NULL)
    {
        FreeEntity(ship);
        return 1;
    }
    yoshi = NewEntity("game/entities/test.entity");
    if(yoshi == NULL)
    {
        FreeEntity(ship);
        FreeEntity(flames);
        return 1;
    }

    bolt = NewEntity("game/entities/bolt.entity");

    ship->center_x          = 120;
    ship->center_y          = 120;
    ship->sprite->z_index   = 3;

    yoshi->center_x         = 220;
    yoshi->center_y         = 120;
    yoshi->a_speed          = 2;
    yoshi->x_speed          = 0;
    yoshi->y_speed          = 0;
    yoshi->sprite->z_index  = 4;
    
    UpdateEntity(ship);
    UpdateEntity(flames);
    UpdateEntity(yoshi);

    bolt->sprite->z_index   = 1;

    bolts = NewList();

    visual_debug = NewPixelMap(640, 480, (Vector){320, 240}, 10);
    ClearPMap(visual_debug);

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
    FreePixelMap(visual_debug);

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
                case SDLK_r :
                    yoshi->center_x = 220;
                    yoshi->center_y = 120;
                    yoshi->x_speed = 0;
                    yoshi->y_speed = 0;
                    ship->center_x = 520;
                    ship->center_y = 120;
                    ship->x_speed = 0;
                    ship->y_speed = 0;
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

            if(CheckCollision(ship->collision_object, yoshi->collision_object) != 0)
            {
                printf("BOOM\n");
                //flags ^= CONTINUE;
                AddForce(ship->physics_object, yoshi->x_speed * yoshi->physics_object->mass, yoshi->y_speed * yoshi->physics_object->mass,
                        ship->physics_object->cog_x, ship->physics_object->cog_y);
                AddForce(yoshi->physics_object, ship->x_speed * ship->physics_object->mass, ship->y_speed * ship->physics_object->mass,
                        yoshi->physics_object->cog_x, yoshi->physics_object->cog_y);
            }
            Element* el = bolts->start;
            Entity* tmp = NULL;
            int i = 0;
            while(el != NULL)
            {
                tmp = (Entity*)el->value;
                //if(CheckCollision(ship->collision_object, tmp->collision_object) != 0)
                //{
                //    printf("BOOM\n");
                //    flags ^= CONTINUE;
                //}
                if(CheckCollision(yoshi->collision_object, tmp->collision_object) != 0)
                {
                    AddForce(yoshi->physics_object, RotateOffsetX(0.0, -10.0, tmp->angle), RotateOffsetY(0.0, -10.0, tmp->angle),
                            yoshi->physics_object->cog_x, yoshi->physics_object->cog_y);
                    yoshi->sprite->zoom -= 0.5;
                    if(yoshi->sprite->zoom < 0.5)
                        yoshi->sprite->zoom = 0.5;
                    FreeEntity(tmp);
                    FreeElement(bolts, i);
                }
                i++;
                el = el->next;
            }

            UpdateEntity(ship);

            flames->angle = ship->angle;
            flames->center_x = ship->center_x + RotateOffsetX(0.0, ship->sprite->h * ship->sprite->zoom, ship->angle);
            flames->center_y = ship->center_y + RotateOffsetY(0.0, ship->sprite->h * ship->sprite->zoom, ship->angle);
            UpdateEntity(flames);

            UpdateEntity(yoshi);
            yoshi->sprite->zoom      += 0.01;
            yoshi->physics_object->mass = yoshi->sprite->zoom * 100;
            if(yoshi->physics_object->mass < 1)
                yoshi->physics_object->mass = 1;
            yoshi->collision_object->radius = 32*yoshi->sprite->zoom;
            if(yoshi->collision_object->radius < 1)
                yoshi->collision_object->radius = 1;

            for(i = 0; i < bolts->size; i++)
            {
                Entity* tmp = (Entity*)GetValue(bolts, i);
                if(tmp->center_x < -15 || tmp->center_y < -15 || tmp->center_x > 1000 || tmp->center_y > 500)
                {
                    FreeEntity(tmp);
                    FreeElement(bolts, i);
                }
                else
                    UpdateEntity(tmp);
            }
        }

        if(flags & DRAW)
        {
            ClearPMap(visual_debug);
            DrawEntity(ship);
            DrawEntityDebugInfo(visual_debug, ship);
            DrawEntity(flames);
            DrawEntity(yoshi);
            DrawEntityDebugInfo(visual_debug, yoshi);
            int i;
            for(i = 0; i < bolts->size; i++)
            {
                Entity* tmp = (Entity*)GetValue(bolts, i);
                DrawEntity(tmp);
                DrawEntityDebugInfo(visual_debug, tmp);
            }
            DrawPixelMap(visual_debug);
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
