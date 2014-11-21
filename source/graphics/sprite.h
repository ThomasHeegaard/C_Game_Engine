/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : sprite.h
|Author   : Thomas Heegaard
|Created  : 10/28/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#ifndef SPRITE_H
#define SPRITE_H

#include "../utils/global_defines.h"
#include "texture_bank.h"

//======================================================================================
//                  DATA
//======================================================================================
typedef struct Sprite
{
    unsigned short  texture_id;

    unsigned int    center_x;
    unsigned int    center_y;
    unsigned char   z_index;
    float           angle;
    float           zoom;

    unsigned short  w;
    unsigned short  h;
    unsigned char   flags;
    char*           data;
} Sprite;


//======================================================================================
//                  DEFINES
//======================================================================================

//========FLAGS==================
#define ANIMATION       1
#define PLAY            2
#define OSCILLATING     4
#define MULTILOOP       8

//========DATA INDICES===========
#define FRAMES          0
#define CURRENT_FRAME   1
#define DIRECTION       2
#define TARGET_FPS      3
#define FRAMES_TO_SKIP  4
#define LOOPS           5
#define CURRENT_LOOP    6

//======================================================================================
//                  FUNCTIONS
//======================================================================================
Sprite* NewSprite(const char* file);

//======================================================================================
ERR RenderSprite(Sprite* sprite);

//======================================================================================
ERR FreeSprite(Sprite* sprite);

//=====================================================================================Ri

#endif //SPRITE_H
