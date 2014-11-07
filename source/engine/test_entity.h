/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : test_entity.h
|Author   : Thomas Heegaard
|Created  : 11/07/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#ifndef TEST_ENTITY_H
#define TEST_ENTITY_H

#include "entity.h"

Entity* NewTestEntity();

ERR     UpdateTestEntity(Entity* entity);

ERR     DrawTestEntity(Entity* entity);

ERR     FreeTestEntity(Entity* entity);

#endif //TEST_ENTITY_H
