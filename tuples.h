#ifndef TUPLES
#define TUPLES
#include <cmath>

#include "float_eq.h"

struct tuple {
  float x, y, z;
  int type;
};

// Operators return a tuple which is the same type as the first parameter
tuple operator+(tuple t1, tuple t2);
tuple operator-(tuple t1, tuple t2);
tuple operator-(tuple t);
tuple operator*(tuple t, float scalar);
// scalar cannot be 0, else 0 vector is returned
tuple operator/(tuple t, float scalar);

// doesn't check if tuples are of the same type
bool operator==(tuple t1, tuple t2);

float norm(tuple t);
tuple normalize(tuple t);

float dot(tuple t1, tuple t2);
// always returns a vector
tuple cross(tuple t1, tuple t2);

const tuple ZEROVEC {0, 0, 0, 0};

#endif
