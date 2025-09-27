#ifndef MATTRANS
#define MATTRANS

#include "matrix.h"

const double PI = 3.141592;

Matrix translate(const tuple& t);
Matrix translate(double x, double y, double z);

Matrix scale(const tuple& t);
Matrix scale(double x, double y, double z);

Matrix roto_x(double rads);
Matrix roto_y(double rads);
Matrix roto_z(double rads);


#endif
