#ifndef RAY
#define RAY

#include <vector>

#include "tuples.h"
#include "matrix_transform.h"

struct intersection;

struct ray {
  tuple origin = ORIGIN;    // should be a point!
  tuple direction = vector(1, 0, 0);    // should be a vector!

  tuple position(double t) const;
  // applies matrix transformation to ray
  ray transform(const Matrix& m) const;
};

struct obj {
  tuple location = ORIGIN;
  Matrix transform = identity(4);

  void set_transform(const Matrix& m);
  void clear_transform();

  obj(tuple loc);

  // make sure to apply inverse transform of object onto ray when implementing
  virtual std::vector<intersection> intersects(const ray& r) const = 0;
};

struct intersection {
  double t;
  const obj* o;
};

// vector from object to ray
tuple obj_to_ray(const obj& o, const ray& r);

const intersection NOINT{0, nullptr};

// given a vector of intersections between object and array, chooses the smallest non-negative time value
// that is returns the intersection which would be when the object "blocks" the ray
intersection hit(const std::vector<intersection>& hits);

#endif
