/*
=================================== ===== ==== === == = =  =   =    =     =
|File     : extra_math.h
|Author   : Thomas Heegaard
|Created  : 12/02/2014
|Purpose  : 
|
|Comments : 
|
=================================== ===== ==== === == = =  =   =    =     =
*/

#ifndef EXTRA_MATH_H
#define EXTRA_MATH_H

#include "global_defines.h"

double RotateOffsetX(double x_offset, double y_offset, double angle);
double RotateOffsetY(double x_offset, double y_offset, double angle);
double Distance(double x_a, double y_a, double x_b, double y_b);

double VectorLength(Vector v);
Vector RotateVector(Vector vector, double angle);
Vector AddVectors(Vector v, Vector u);
Vector VectorMult(Vector v, double x);
Vector unitaryVector(Vector v);
double DotProduct(Vector v, Vector u);
Vector ProjectVector(Vector from, Vector to);

double DVectorLength(DVector v);
DVector RotateDVector(DVector vector, double angle);
DVector AddDVectors(DVector v, DVector u);
DVector DVectorMult(DVector v, double x);
DVector unitaryDVector(DVector v);
double DotProduct(DVector v, DVector u);
DVector ProjectDVector(DVector from, DVector to);

#endif //EXTRA_MATH_H
