/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : test_entity.c
|Author   : Thomas Heegaard
|Created  : 11/07/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#include "test_entity.h"
#include "../graphics/graphics.h"
#include "entity_bank.h"
#include <stdlib.h>

Entity* NewTestEntity()
{
    Entity* entity = (Entity*)malloc(sizeof(Entity));
    if(entity == NULL)
        return NULL;

    entity->type                = TEST_ENTITY;
    entity->flags               = 0;
    entity->center_x            = 0.0;
    entity->center_y            = 0.0;
    entity->angle               = 0.0;
    entity->x_speed             = 0.0;
    entity->y_speed             = 0.0;
    entity->angular_speed       = 0.0;
    entity->bounding_diameter   = 91;

    
    entity->sprite = NewSprite(EXAMPLE1_TEX, (ANIMATION | OSCILLATING | PLAY));
    if(entity->sprite == NULL)
    {
        free(entity);
        return NULL;
    }

    entity->sprite->w                   = 64;
    entity->sprite->h                   = 64;
    entity->sprite->zoom                = 1.0;
    entity->sprite->z_index             = 3;
    entity->sprite->data[FRAMES]        = 8;
    entity->sprite->data[TARGET_FPS]    = 15;
   
    return entity; 
}

ERR UpdateTestEntity(Entity* entity)
{
    if(entity == NULL)
        return 1;
    if(entity->sprite == NULL)
        return 1;
    
    entity->center_x        += entity->x_speed;
    entity->center_y        += entity->y_speed;
    entity->angle           += entity->angular_speed;

    entity->sprite->center_x = entity->center_x;
    entity->sprite->center_y = entity->center_y;
    entity->sprite->angle    = entity->angle;
    return 0;
}

ERR DrawTestEntity(Entity* entity)
{
    if(entity == NULL)
        return 1;
    if(entity->sprite == NULL)
        return 1;

    return DrawSprite(entity->sprite);   
}

ERR FreeTestEntity(Entity* entity)
{
    if(entity == NULL)
        return 1;
    ERR err = 0;
    if(entity->sprite == NULL)
        err++;
    else
        err += FreeSprite(entity->sprite);
    free(entity);
    return err;
}

