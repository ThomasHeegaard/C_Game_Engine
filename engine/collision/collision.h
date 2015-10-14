/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : collision.h
|Author   : Thomas Heegaard
|Created  : 03/05/2015
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#ifndef COLLISION_H
#define COLLISION_H

typedef struct QNode
{
    int x_min;
    int x_max;
    int y_min;
    int y_max;
    List* objects;
    struct QNode* top_left;
    struct QNode* top_right;
    struct QNode* bottom_left;
    struct QNode* bottom_right;
}
QNode;

typedef struct Collision
{
    Entity* 
}

#endif //COLLISION_H
