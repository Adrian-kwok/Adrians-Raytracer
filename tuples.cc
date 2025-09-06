#include "tuples.h"

tuple::tuple(float x, float y, float z): x{x}, y{y}, z{z} {}
tpoint::tpoint(float x, float y, float z): tuple{x,y,z} {}
tvector::tvector(float x, float y, float z): tuple{x,y,z} {}
tcolor::tcolor(float x, float y, float z): tuple{x,y,z} {}
