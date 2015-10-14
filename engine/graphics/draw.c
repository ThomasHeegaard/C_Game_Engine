/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : draw.c
|Author   : Thomas Heegaard
|Created  : 03/07/2015
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#include <math.h>
#include "draw.h"
#include "extra_math.h"

int ColorToARGB(Color color)
{
    return ((int)color.a << 24) | ((int)color.r << 16) | ((int)color.g << 8) | ((int)color.b);
}

ERR DrawPointXY(PixelMap* pm, Color color, int x, int y)
{
    if(pm == NULL)
    {
        fprintf(stderr, "Drawing to NULL pixel map\n");
        return 1;
    }

    if(x > pm->w || x < 0 || x < 0 || x < 0 || x < 0 || x < 0 || x < 0 || x < 0 || y > pm->h || y < 0)
        return 1;

    int argb = ColorToARGB(color);

    pm->pixels[x + pm->w*y] = argb;

    return 0;
}

ERR DrawPoint(PixelMap* pm, Vector pos, Color color)
{
    return DrawPointXY(pm, color, pos.x, pos.y);
}

ERR DrawLine(PixelMap* pm, Vector start, Vector end, Color color)
{

	int     x = start.x;
	int     y = start.y;
	double  slope;
	int     dirX;
	int     dirY;
	double  dirS;

	if(start.x < end.x)	dirX = 1;
	else			    dirX = -1;
	if(start.y < end.y)	dirY = 1;
	else			    dirY = -1;


    if(DrawPointXY(pm, color, x, y) != 0)
        return 1;

    if(start.x == end.x)
    {
        while(y != end.y)
        {
            y += dirY;
            if(DrawPointXY(pm, color, x, y) != 0)
                return 1;
        }
        return 0;
    }

    if(start.y == end.y)
    {
        while(x != end.x)
        {
            x += dirX;
            if(DrawPointXY(pm, color, x, y) != 0)
                return 1;
        }
        return 0;
    }

    
    slope = (double)(end.x - start.x)/(double)(end.y - start.y);
    dirS =  (double)(dirX*dirY);

    while(x != end.x)
    {
        x += dirX;
        while(dirS * (double)(end.x - x) / (double)(end.y - y) < dirS * slope && y != end.y )
        {
            y += dirY;
            if(DrawPointXY(pm, color, x, y) != 0)
                return 1;
        }
    }

    return 0;
}

ERR DrawAngle(PixelMap* pm, Vector start, float angle, int length, Color color)
{
    if(length == 0)
        return 0;
    return DrawLine(pm, start, RotateVector((Vector){start.x, start.y + length}, angle), color);
}

ERR DrawArrow(PixelMap* pm, Vector start, float angle, int length, Color color)
{
    int err = 0;
    Vector end = RotateVector((Vector){start.x, end.x + length}, angle);
    err += DrawLine(pm, start, end, color);
    err += DrawAngle(pm, end, angle + 45.0, length / 5, color);
    err += DrawAngle(pm, end, angle - 45.0, length / 5, color);
    return err;
}

ERR DrawCircle(PixelMap* pm, Vector center, int radius, Color color)
{
    int x = radius;
    int y = 0;
    int radiusError = 1-x;
    ERR err = 0;

    while(x >= y)
    {
        err += DrawPointXY(pm, color, x + center.x, y + center.y);
        err += DrawPointXY(pm, color, y + center.x, x + center.y);
        err += DrawPointXY(pm, color, -x + center.x, y + center.y);
        err += DrawPointXY(pm, color, -y + center.x, x + center.y);
        err += DrawPointXY(pm, color, -x + center.x, -y + center.y);
        err += DrawPointXY(pm, color, -y + center.x, -x + center.y);
        err += DrawPointXY(pm, color, x + center.x, -y + center.y);
        err += DrawPointXY(pm, color, y + center.x, -x + center.y);
        y++;
        if(radiusError < 0)
        {
            radiusError += 2 * y + 1;
        }
        else
        {
            x--;
            radiusError += 2 * (y - x) + 1;
        }
    }
    return err;
}

ERR FillPMap(PixelMap* pm, Color color)
{
    if(pm == NULL)
    {
        fprintf(stderr, "Drawing to NULL pixel map\n");
        return 1;
    }

    int argb = ColorToARGB(color);
    int i;
    for(i = 0; i < pm->w * pm->h; i++)
        pm->pixels[i] = argb;

    return 0;
}

ERR ClearPMap(PixelMap* pm)
{
    if(pm == NULL)
    {
        fprintf(stderr, "Drawing to NULL pixel map\n");
        return 1;
    }

    int i;
    for(i = 0; i < pm->w * pm->h; i++)
        pm->pixels[i] = 0;

    return 0;
}
