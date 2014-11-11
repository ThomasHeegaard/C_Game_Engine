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
#include "entity_bank.h"
#include "../graphics/graphics.h"
#include "../utils/config_loader.h"
#include <stdlib.h>

Entity* NewEntity(unsigned short type)
{
    switch(type)
    {
        case TEST_ENTITY: return NewTestEntity();
        case SHIP_ENTITY: return NewShipEntity();
    }
    return NULL;
}

ERR UpdateEntity(Entity* entity)
{
    if(entity == NULL)
        return 1;

    switch(entity->type)
    {
        case TEST_ENTITY: return UpdateTestEntity(entity); 
        case SHIP_ENTITY: return UpdateShipEntity(entity);
    }
    return 1;
}

ERR DrawEntity(Entity* entity)
{
    if(entity == NULL)
        return 1;

    switch(entity->type)
    {
        case TEST_ENTITY: return DrawSprite(entity->sprite);
        case SHIP_ENTITY: return DrawSprite(entity->sprite);
    }
    return 1;
}

ERR FreeEntity(Entity* entity)
{
    if(entity == NULL)
        return 1;
    
    switch(entity->type)
    {
        case TEST_ENTITY: return FreeTestEntity(entity);
        case SHIP_ENTITY: return FreeShipEntity(entity);
    }

    if(entity->sprite != NULL)
        FreeSprite(entity->sprite);
    free(entity);
    return 1;
}

Entity* LoadEntity(const char* entity_file)
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
   
    return entity; 
}
