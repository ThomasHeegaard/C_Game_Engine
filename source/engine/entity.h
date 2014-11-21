/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : entity.h
|Author   : Thomas Heegaard
|Created  : 11/07/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#ifndef ENTITY_H
#define ENTITY_H

#include "../utils/global_defines.h"
#include "../graphics/sprite.h"

typedef struct Entity
{
    unsigned short  type;
    unsigned char   flags;

    double          center_x;
    double          center_y;
    float           angle;
    double          x_speed;
    double          y_speed;
    float           angular_speed;

    unsigned short  bounding_diameter;

    Sprite*         sprite;
} Entity;

Entity* NewEntity(const char* entity_file);

ERR     UpdateEntity(Entity* entity);

ERR     DrawEntity(Entity* entity);

ERR     FreeEntity(Entity* entity);

#endif //ENTITY_H
