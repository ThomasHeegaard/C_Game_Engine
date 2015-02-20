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
#include "graphics.h"
#include "config_loader.h"
#include <stdlib.h>
#include <stdio.h>

Entity* NewEntity(const char* entity_file)
{
    if(OpenConfigFile(entity_file) != 0)
    {
        fprintf(stderr, "No entity file - Loading entity %s failed\n", entity_file);
        return NULL;
    }

    if(GetParameterInt("FLAGS") & CUSTOM_INIT)
    {
        switch(GetParameterInt("ENTITYTYPE"))
        {

        default:
            fprintf(stderr, "No custom initializer found for entity %s\n", entity_file);
            CloseConfigFile();
            return NULL;
        }
    }

    Entity* entity = (Entity*)malloc(sizeof(Entity));
    if(entity == NULL)
    {
        fprintf(stderr, "Memory allocation failure - Loading entity %s failed\n", entity_file);
        return NULL;
    }

    entity->type                = GetParameterInt("TYPE");
    entity->flags               = GetParameterInt("FLAGS");
    entity->center_x            = 0.0;
    entity->center_y            = 0.0;
    entity->angle               = 0.0;
    entity->x_speed             = 0.0;
    entity->y_speed             = 0.0;
    entity->angular_speed       = 0.0;
    entity->bounding_diameter   = GetParameterInt("BOUNDINGDIAMETER");

    char* sprite_file = (char*)malloc(VALUE_LENGTH * sizeof(char));
    if(sprite_file == NULL)
    {
        CloseConfigFile();
        free(entity);
        fprintf(stderr, "Memory allocation error\n");
        return NULL;
    }
    GetParameterStr("SPRITE", sprite_file);

    CloseConfigFile();
    
    entity->sprite = NewSprite(sprite_file);

    free(sprite_file);

    if(entity->sprite == NULL)
    {
        free(entity);
        fprintf(stderr, "Loading sprite failed - Loading entity %s failed\n", entity_file);
        return NULL;
    }

    return entity; 
}

ERR UpdateEntity(Entity* entity)
{
    if(entity == NULL)
        return 1;
    if(entity->flags & CUSTOM_UPDATE)
    {
        switch(entity->type)
        {

        default:
            fprintf(stderr, "No custom updater found for entity \n");
            return 1;
        }
    }
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
    if(entity->flags & CUSTOM_DRAW)
    {
        switch(entity->type)
        {

        default:
            fprintf(stderr, "No custom draw function found for entity\n");
            return 1;
        }
    }
    if(entity->sprite == NULL)
        return 1;

    return DrawSprite(entity->sprite);   
}

ERR FreeEntity(Entity* entity)
{
    if(entity == NULL)
        return 1;
    if(entity->flags & CUSTOM_EXIT)
    {
        switch(entity->type)
        {

        default:
            fprintf(stderr, "No custom exit function found for entity\n");
            return 1;
        }
    }
    ERR err = 0;
    if(entity->sprite == NULL)
        err++;
    else
    {
        err += FreeSprite(entity->sprite);
    }
    entity->sprite = NULL;
    free(entity);
    return err;
}

