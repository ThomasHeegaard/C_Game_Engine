/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : draw.h
|Author   : Thomas Heegaard
|Created  : 03/07/2015
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#ifndef DRAW_H
#define DRAW_H

#include "sdl_wrapper.h"

typedef struct Color
{
    unsigned char a;
    unsigned char r;
    unsigned char g;
    unsigned char b;
}
Color;

#define TRANSP (Color){0, 0, 0, 0}
#define BLACK (Color){255, 0, 0, 0}
#define RED (Color){255, 255, 0, 0}
#define GREEN (Color){255, 0, 255, 0}
#define BLUE (Color){255, 0, 0, 255}
#define GREY (Color){255, 150, 150, 150}
#define WHITE (Color){255, 255, 255, 255}

ERR DrawPoint(PixelMap* pm, Vector pos, Color color);
ERR DrawLine(PixelMap* pm, Vector start, Vector end, Color color);
ERR DrawAngle(PixelMap* pm, Vector start, float angle, int length, Color color);
ERR DrawArrow(PixelMap* pm, Vector start, float angle, int length, Color color);
ERR DrawCircle(PixelMap* pm, Vector center, int radius, Color color);
ERR FillPMap(PixelMap* pm, Color color);
ERR ClearPMap(PixelMap* pm);


#endif //DRAW_H
