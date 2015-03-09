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
    entity->a_speed             = 0.0;
    entity->bounding_diameter   = GetParameterInt("BOUNDINGDIAMETER");
    entity->sprite              = NULL;
    entity->physics_object      = NULL;
    entity->collision_object    = NULL;

    if(entity->flags & HAS_PHYSICS)
    {
        entity->physics_object = NewPhysicsObject();
        if(entity->physics_object == NULL)
        {
            free(entity);
            fprintf(stderr, "Creating physics object failed\n");
            return NULL;
        }
        entity->physics_object->mass = GetParameterInt("MASS");
        if(entity->physics_object->mass <= 0.1)
            entity->physics_object->mass = 1.0;
    }

    if(entity->flags & HAS_COLLISION)
    {
        entity->collision_object = NewCollisionObject();
        if(entity->collision_object == NULL)
        {
            FreePhysicsObject(entity->physics_object);
            free(entity);
            fprintf(stderr, "Creating collision object failed\n");
            return NULL;
        }
        entity->collision_object->radius = entity->bounding_diameter;
    }

    if(entity->flags & HAS_SPRITE)
    {
        char* sprite_file = (char*)malloc(VALUE_LENGTH * sizeof(char));
        if(sprite_file == NULL)
        {
            CloseConfigFile();
            if(entity->flags & HAS_PHYSICS)
                FreePhysicsObject(entity->physics_object);
            if(entity->flags & HAS_COLLISION)
                FreeCollisionObject(entity->collision_object);
            free(entity);
            fprintf(stderr, "Memory allocation error\n");
            return NULL;
        }
        GetParameterStr("SPRITE", sprite_file);

        entity->sprite = NewSprite(sprite_file);

        free(sprite_file);

        if(entity->sprite == NULL)
        {
            CloseConfigFile();
            if(entity->flags & HAS_PHYSICS)
                FreePhysicsObject(entity->physics_object);
            if(entity->flags & HAS_COLLISION)
                FreeCollisionObject(entity->collision_object);
            free(entity);
            fprintf(stderr, "Loading sprite failed - Loading entity %s failed\n", entity_file);
            return NULL;
        }
    }

    CloseConfigFile();

    return entity; 
}

Entity* CopyEntity(Entity* original)
{
    if(original->flags & CUSTOM_INIT)
    {
        switch(original->type)
        {

        default:
            fprintf(stderr, "No custom initializer found for copied entity (IMPOSSIBLE!)\n");
            return NULL;
        }
    }

    Entity* entity = (Entity*)malloc(sizeof(Entity));
    if(entity == NULL)
    {
        fprintf(stderr, "Memory allocation failure - copying entity failed\n");
        return NULL;
    }

    entity->type                = original->type;
    entity->flags               = original->flags;
    entity->center_x            = original->center_x;
    entity->center_y            = original->center_y;
    entity->angle               = original->angle;
    entity->x_speed             = original->x_speed;
    entity->y_speed             = original->y_speed;
    entity->a_speed             = original->a_speed;
    entity->bounding_diameter   = original->bounding_diameter;
    entity->sprite              = NULL;
    entity->physics_object      = NULL;

    if(entity->flags & HAS_PHYSICS)
    {
        entity->physics_object = CopyPhysicsObject(original->physics_object);
        if(entity->physics_object == NULL)
        {
            free(entity);
            fprintf(stderr, "Copying physics object failed\n");
            return NULL;
        }
    }

    if(entity->flags & HAS_COLLISION)
    {
        entity->collision_object = CopyCollisionObject(original->collision_object);
        if(entity->collision_object == NULL)
        {
            if(entity->flags & HAS_PHYSICS)
                FreePhysicsObject(entity->physics_object);
            free(entity);
            fprintf(stderr, "Copying collision object failed\n");
            return NULL;
        }
    }

    if(entity->flags & HAS_SPRITE)
    {
        entity->sprite = CopySprite(original->sprite);

        if(entity->sprite == NULL)
        {
            if(entity->flags & HAS_PHYSICS)
                FreePhysicsObject(entity->physics_object);
            if(entity->flags & HAS_COLLISION)
                FreeCollisionObject(entity->collision_object);
            free(entity);
            fprintf(stderr, "copying sprite failed - copying entity failed\n");
            return NULL;
        }
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

    if(entity->flags & HAS_PHYSICS)
    {
        ApplyForces(entity->physics_object);
        entity->x_speed         += entity->physics_object->a_x;
        entity->y_speed         += entity->physics_object->a_y;
        entity->a_speed         += entity->physics_object->a_alpha;
        entity->physics_object->cog_x = entity->center_x;
        entity->physics_object->cog_y = entity->center_y;
    }
    
    entity->center_x        += entity->x_speed;
    entity->center_y        += entity->y_speed;
    entity->angle           += entity->a_speed;

    if(entity->flags & HAS_COLLISION)
    {
        entity->collision_object->center_x = entity->center_x;
        entity->collision_object->center_y = entity->center_y;
    }

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

