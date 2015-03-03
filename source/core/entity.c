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

    int flags = GetParameterInt("FLAGS");

    if(flags & CUSTOM_INIT)
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
    entity->flags               = flags;
    entity->center_x            = 0.0;
    entity->center_y            = 0.0;
    entity->angle               = 0.0;
    entity->x_speed             = 0.0;
    entity->y_speed             = 0.0;
    entity->angular_speed       = 0.0;
    entity->bounding_diameter   = GetParameterInt("BOUNDINGDIAMETER");
    entity->sprite              = NULL;
    entity->physics_object      = NULL;

    if(entity->flags & HAS_SPRITE)
    {
        char* sprite_file = (char*)malloc(VALUE_LENGTH * sizeof(char));
        if(sprite_file == NULL)
        {
            CloseConfigFile();
            free(entity);
            fprintf(stderr, "Memory allocation error\n");
            return NULL;
        }
        GetParameterStr("SPRITE", sprite_file);

        entity->sprite = NewSprite(sprite_file);

        free(sprite_file);

        if(entity->sprite == NULL)
        {
            free(entity);
            fprintf(stderr, "Loading sprite failed - Loading entity %s failed\n", entity_file);
            return NULL;
        }
    }

    if(entity->flags & HAS_PHYSICS)
    {
        entity->physics_object = NewPhysicsObject();
        if(entity->physics_object == NULL)
        {
            FreeSprite(entity->sprite);
            free(entity);
            fprintf(stderr, "Creating physics object failed\n");
            return NULL;
        }
        entity->physics_object->mass = GetParameterInt("MASS");
        if(entity->physics_object->mass <= 0.1)
            entity->physics_object->mass = 1.0;
    }

    CloseConfigFile();

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

    if(entity->flags & HAS_PHYSICS)
    {
        ApplyForces(entity->physics_object);
        entity->x_speed         += entity->physics_object->a_x;
        entity->y_speed         += entity->physics_object->a_y;
        entity->angular_speed   += entity->physics_object->a_alpha;
        entity->physics_object->cog_x = entity->center_x;
        entity->physics_object->cog_y = entity->center_y;
    }
    
    entity->center_x        += entity->x_speed;
    entity->center_y        += entity->y_speed;
    entity->angle           += entity->angular_speed;

    if(entity->flags & HAS_SPRITE)
    {
        if(entity->sprite == NULL)
            return 1;
        entity->sprite->center_x = entity->center_x;
        entity->sprite->center_y = entity->center_y;
        entity->sprite->angle    = entity->angle;
    }
    return 0;
}

ERR DrawEntity(Entity* entity)
{
    if(entity == NULL)
        return 1;
    if((entity->flags & HAS_SPRITE) == 0)
        return 0;
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

    if(entity->flags & HAS_SPRITE)
    {
        err += FreeSprite(entity->sprite);
        entity->sprite = NULL;
    }

    if(entity->flags & HAS_PHYSICS)
    {
        err += FreePhysicsObject(entity->physics_object);
        entity->physics_object = NULL;
    }

    free(entity);
    return err;
}

