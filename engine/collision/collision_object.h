/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : collision_object.h
|Author   : Thomas Heegaard
|Created  : 01/20/2015
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#ifndef COLLISION_OBJECT_H
#define COLLISION_OBJECT_H

#include "global_defines.h"
#include "list.h"

typedef struct CollisionElement
{
    unsigned char   shape;
    int             x_offset;
    int             y_offset;
    int             width;
    int             height;
    double          angular_offset;
}
CollisionElement;

typedef struct CollisionObject
{
    int                 center_x;
    int                 center_y;
    int                 radius;
    unsigned char       element_count;
    List*  elements;   
}
CollisionObject;


#define SQUARE_SHAPE 0
#define CIRCLE_SHAPE 1


CollisionObject* NewCollisionObject();

CollisionObject* CopyCollisionObject(CollisionObject* original);

ERR AddCollisionElement(CollisionObject* obj, unsigned char shape, int dx, int dy, int w, int h, double da);
    //Adds a collision element to the object, at offsets dx, dy, da to the center of that element

ERR FreeCollisionObject(CollisionObject* obj);

ERR CheckCollision(CollisionObject* obj_a, CollisionObject* obj_b);



#endif //COLLISION_OBJECT_H
