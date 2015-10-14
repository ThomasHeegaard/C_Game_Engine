/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : global_defines.h
|Author   : Thomas Heegaard
|Created  : 10/28/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#ifndef GLOBAL_DEFINES_H
#define GLOBAL_DEFINES_H

#define ERR unsigned char

typedef struct Vector
{
    int x;
    int y;
}
Vector;

typedef struct DVector
{
    double x;
    double y;
}
DVector;

#endif //GLOBAL_DEFINES_H
