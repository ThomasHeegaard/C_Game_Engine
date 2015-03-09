/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : extra_math.c
|Author   : Thomas Heegaard
|Created  : 12/02/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/
#include <math.h>
#include <stdio.h>
#define PI 3.14159265

double RotateOffsetX(double x_offset, double y_offset, double angle)
{
    angle = angle * PI / 180;
    return cos(angle)*x_offset - sin(angle)*y_offset;
}
double RotateOffsetY(double x_offset, double y_offset, double angle)
{
    angle = angle * PI / 180;
    return cos(angle)* y_offset + sin(angle)*x_offset; 
}
int Distance(int x_a, int y_a, int x_b, int y_b)
{
    int dx = x_b - x_a;
    int dy = y_b - y_a;
    return sqrt(dx*dx - dy*dy);
}

