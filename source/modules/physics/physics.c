/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : physics.c
|Author   : Thomas Heegaard
|Created  : 12/02/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#include <stdlib.h>
#include <stdio.h>
#include "physics.h"

Force* NextForce(List* forces)
{
    if(forces->size == 0)
        return NULL;
    Force* tmp = (Force*)GetValue(forces, 0);
    FreeElement(forces, 0);
    return tmp;
}

PhysicsObject* NewPhysicsObject()
{
    PhysicsObject* phys = (PhysicsObject*)malloc(sizeof(PhysicsObject));
    phys->cog_x     = 0;
    phys->cog_y     = 0;
    phys->a_x       = 0;
    phys->a_y       = 0;
    phys->a_alpha   = 0;
    phys->forces    = NewList();
    return phys;
}

ERR AddForce(PhysicsObject* target, double x_force, double y_force, double x_pos, double y_pos)
{
    Force* force = (Force*)malloc(sizeof(Force));
    if(force == NULL)
    {
        fprintf(stderr, "Memory allocation failure");
        return 1;
    }
    force->x_force  = x_force;
    force->y_force  = y_force;
    force->x_pos    = x_pos;
    force->y_pos    = y_pos;
    return InsertValue(force, target->forces, 0);
}

ERR ApplyForces(PhysicsObject* object)
{
    object->a_alpha = 0;
    object->a_x     = 0;
    object->a_y     = 0;

    Force* force = NextForce(object->forces);
    while(force != NULL)
    {
        object->a_alpha += ((force->x_pos - object->cog_x)*force->y_force - (force->y_pos - object->cog_y)*force->x_force)/object->mass;
        object->a_x     += force->x_force/object->mass;
        object->a_y     += force->y_force/object->mass;
        free(force);
        force = NextForce(object->forces);
    }

    return 0;
}

ERR FreePhysicsObject(PhysicsObject* object)
{
    Force* tmp = NextForce(object->forces);
    while(tmp != NULL)
    {
        free(tmp);   
        Force* tmp = NextForce(object->forces);
    }
    ClearList(object->forces);
    free(object);
    return 0;
}
