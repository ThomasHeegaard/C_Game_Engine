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
