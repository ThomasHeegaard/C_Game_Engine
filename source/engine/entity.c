/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : entity.c
|Author   : Thomas Heegaard
|Created  : 11/07/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#include "entity.h"
#include "../graphics/graphics.h"
#include "../utils/config_loader.h"
#include <stdlib.h>

Entity* NewEntity(const char* entity_file)
{
    if(OpenConfigFile(entity_file) != 0)
        return NULL;

    Entity* entity = (Entity*)malloc(sizeof(Entity));
    if(entity == NULL)
        return NULL;

    entity->type                = GetParameterInt("ENTITYTYPE");
    entity->flags               = 0;
    entity->center_x            = 0.0;
    entity->center_y            = 0.0;
    entity->angle               = 0.0;
    entity->x_speed             = 0.0;
    entity->y_speed             = 0.0;
    entity->angular_speed       = 0.0;
    entity->bounding_diameter   = GetParameterInt("BOUNDINGDIAMETER");

    
    entity->sprite = NewSprite(GetParameterInt("SPRITENAME"), GetParameterInt("SPRITEFLAGS"));
    if(entity->sprite == NULL)
    {
        free(entity);
        return NULL;
    }

    entity->sprite->w                   = GetParameterInt("SPRITEWIDTH");
    entity->sprite->h                   = GetParameterInt("SPRITEHEIGHT");
    entity->sprite->zoom                = GetParameterInt("SPRITEZOOM");
    entity->sprite->z_index             = GetParameterInt("SPRITEZINDEX");

    if(entity->sprite->flags & ANIMATION)
    {
        entity->sprite->data[FRAMES]    = GetParameterInt("SPRITEFRAMES");
        entity->sprite->data[TARGET_FPS]= GetParameterInt("SPRITETARGETFPS");
        if(entity->sprite->flags & MULTILOOP)
            entity->sprite->data[LOOPS] = GetParameterInt("SPRITELOOPS");
    }
   
    CloseConfigFile();
    return entity; 
}

ERR UpdateEntity(Entity* entity)
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

ERR DrawEntity(Entity* entity)
{
    if(entity == NULL)
        return 1;
    if(entity->sprite == NULL)
        return 1;

    return DrawSprite(entity->sprite);   
}

ERR FreeEntity(Entity* entity)
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

