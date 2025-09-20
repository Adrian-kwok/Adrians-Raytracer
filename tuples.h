#ifndef TUPLES
#define TUPLES
#include <cmath>

#include "float_eq.h"

struct tuple {
  float x, y, z, w;

  // these are to make working with for loops easier
  void set(int i, float val);
  float get(int i) const;
};

tuple point(float x, float y, float z);
tuple vector(float x, float y, float z);

tuple operator+(tuple t1, tuple t2);
tuple operator-(tuple t1, tuple t2);
tuple operator-(tuple t);
tuple operator*(tuple t, float scalar);
// scalar cannot be 0, else 0 vector is returned
tuple operator/(tuple t, float scalar);

bool operator==(tuple t1, tuple t2);

float norm(tuple t);
tuple normalize(tuple t);

float dot(tuple t1, tuple t2);
// always returns a vector
tuple cross(tuple t1, tuple t2);

const tuple ZEROVEC {0, 0, 0, 0};

#endif
