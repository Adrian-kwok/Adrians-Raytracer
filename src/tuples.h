#ifndef TUPLES
#define TUPLES
#include <cmath>

#include "double_eq.h"

struct tuple {
  double x, y, z, w;

  // these are to make working with for loops easier
  void set(int i, double val);
  double get(int i) const;
};

tuple point(double x, double y, double z);
tuple vector(double x, double y, double z);

tuple operator+(tuple t1, tuple t2);
tuple operator-(tuple t1, tuple t2);
tuple operator-(tuple t);
tuple operator*(tuple t, double scalar);
// scalar cannot be 0, else 0 vector is returned
tuple operator/(tuple t, double scalar);

bool operator==(tuple t1, tuple t2);

double norm(tuple t);
tuple normalize(tuple t);

double dot(tuple t1, tuple t2);
// always returns a vector
tuple cross(tuple t1, tuple t2);

// both should be vectors
tuple reflect(tuple v, tuple norm);

const tuple ZEROVEC{0, 0, 0, 0};
const tuple ORIGIN{0, 0, 0, 1};

#endif
