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

#include "global_defines.h"
#include "sdl_wrapper.h"
#include "sprite.h"

ERR DrawSprite(Sprite* sprite);
ERR DrawPixelMap(PixelMap* pm);
ERR Render();

#endif //GRAPHICS_H
