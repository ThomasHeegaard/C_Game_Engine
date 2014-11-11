/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : ship_entity.c
|Author   : Thomas Heegaard
|Created  : 11/07/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#include "ship_entity.h"
#include "../graphics/graphics.h"
#include "entity_bank.h"
#include <stdlib.h>

Entity* NewShipEntity()
{
    Entity* entity = (Entity*)malloc(sizeof(Entity));
    if(entity == NULL)
        return NULL;

    entity->type                = SHIP_ENTITY;
    entity->flags               = 0;
    entity->center_x            = 0.0;
    entity->center_y            = 0.0;
    entity->angle               = 0.0;
    entity->x_speed             = 0.0;
    entity->y_speed             = 0.0;
    entity->angular_speed       = 0.0;
    entity->bounding_diameter   = 91;

    
    entity->sprite = NewSprite(SHIP1_TEX, 0);
    if(entity->sprite == NULL)
    {
        free(entity);
        return NULL;
    }

    entity->sprite->w                   = 16;
    entity->sprite->h                   = 16;
    entity->sprite->zoom                = 4.0;
    entity->sprite->z_index             = 3;
   
    return entity; 
}

ERR UpdateShipEntity(Entity* entity)
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

ERR DrawShipEntity(Entity* entity)
{
    if(entity == NULL)
        return 1;
    if(entity->sprite == NULL)
        return 1;

    return DrawSprite(entity->sprite);   
}

ERR FreeShipEntity(Entity* entity)
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

