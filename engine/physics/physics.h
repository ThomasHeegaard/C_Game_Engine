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

#include "global_defines.h"
#include "list.h"

typedef struct Force
{
    double x_force;
    double y_force;
    double x_pos;
    double y_pos;
} Force;

typedef struct PhysicsObject
{
    double  mass;
    double  cog_x;
    double  cog_y;
    double  a_x;
    double  a_y;
    double  a_alpha;
    List*   forces;
} PhysicsObject;

PhysicsObject* NewPhysicsObject();

PhysicsObject* CopyPhysicsObject(PhysicsObject* original);

ERR AddForce(PhysicsObject* target, double x_force, double y_force, double x_pos, double y_pos);

ERR ApplyForces(PhysicsObject* object);

ERR FreePhysicsObject(PhysicsObject* object);

#endif //PHYSICS_H
