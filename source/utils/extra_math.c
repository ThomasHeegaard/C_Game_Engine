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
