/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : physics.h
|Author   : Thomas Heegaard
|Created  : 12/02/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#ifndef PHYSICS_H
#define PHYSICS_H

#include "../utils/global_defines.h"
#include "../utils/list.h"

typedef struct Force
{
    double x_force;
    double y_force;
    double x_pos;
    double y_pos;
} Force;

typedef struct PhysicsObject
{
    double mass;
    double cog_x;
    double cog_y;
    double a_x;
    double a_y;
    double a_alpha;
    List*  forces;
} PhysicsObject;

PhysicsObject* NewPhysicsObject();

ERR AddForce(PhysicsObject* target, double x_force, double y_force, double x_pos, double y_pos);

ERR ApplyForces(PhysicsObject* object);

ERR FreePhysicsObject();

#endif //PHYSICS_H
