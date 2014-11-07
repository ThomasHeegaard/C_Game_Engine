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


Entity* NewEntity(unsigned short type)
{
    Entity* entity = (Entity*)malloc(sizeof(Entity));
    if(entity == NULL)
        return NULL;

    switch(type)
    {
    default:
    {
        free(entity);
        return NULL;
    }
    }
    return entity;
}

ERR UpdateEntity(Entity* entity)
{
    if(entity == NULL)
        return 1;

    switch(entity->type)
    {
    
    default:
        return 1;
    }
    return 1;
}

ERR DrawEntity(Entity* entity)
{
    if(entity == NULL)
        return 1;
    return DrawSprite(entity->sprite);
}

ERR FreeEntity(Entity* entity)
{
    if(entity == NULL)
        return 1;
    
    ERR error = 0;
    switch(entity->type)
    {
    
    default:
        error += 1;
    }
    free(entity);
    return error;
}
