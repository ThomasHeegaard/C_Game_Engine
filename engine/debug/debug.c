/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : debug.c
|Author   : Thomas Heegaard
|Created  : 03/09/2015
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#include "debug.h"

void DrawEntityDebugInfo(PixelMap* pm, Entity* entity)
{
    int radius;
    if(entity->flags & HAS_COLLISION)
        radius = entity->collision_object->radius;
    else
        radius = entity->bounding_radius;
    DrawCircle(pm, (Vector){entity->center_x, entity->center_y}, radius, GREEN);
    DrawLine(pm, (Vector){entity->center_x, entity->center_y},
            (Vector){entity->center_x + 5*entity->x_speed, entity->center_y + 5*entity->y_speed}, RED);
}

