/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : ship_entity.h
|Author   : Thomas Heegaard
|Created  : 11/07/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#ifndef SHIP_ENTITY_H
#define SHIP_ENTITY_H

#include "entity.h"

Entity* NewShipEntity();

ERR     UpdateShipEntity(Entity* entity);

ERR     DrawShipEntity(Entity* entity);

ERR     FreeShipEntity(Entity* entity);

#endif //SHIP_ENTITY_H
