/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : graphics.h
|Author   : Thomas Heegaard
|Created  : 11/06/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "../utils/global_defines.h"
#include "sprite.h"

ERR DrawSprite(Sprite* sprite);
ERR Render();

#endif //GRAPHICS_H
