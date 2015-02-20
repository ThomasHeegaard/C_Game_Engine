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

typedef struct Collision_Element
{
    unsigned char   shape;
    int             x_offset;
    int             y_offset;
    int             width;
    int             height;
    double          angle;
}
Shape;

typedef struct Collision_Object
{
    int                 center_x;
    int                 center_y;
    int                 max_radius;
    unsigned char       element_count;
    Collision_Element*  elements;   
}
Collision_Object;

Collision_Object* NewCollisionObject(int c_x, int c_y);

ERR AddCollisionElement(Collision_Object* obj, unsigned char shape, int x, int y, int w, int h, int a);

ERR FreeCollisionObject(Collision_Object* obj);

ERR CheckCOllision(Collision_Object* obj_a, Collision_Object* obj_b);

#define SQUARE_SHAPE 0;
#define CIRCLE_SHAPE 1;


#endif //COLLISION_OBJECT_H
