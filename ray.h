#ifndef RAY
#define RAY

#include <vector>

#include "matrix_transform.h"
#include "tuples.h"

struct intersection;

struct ray {
  tuple origin = ORIGIN;              // should be a point!
  tuple direction = vector(1, 0, 0);  // should be a vector!

  tuple position(double t) const;
  // applies matrix transformation to ray
  ray transform(const Matrix& m) const;
};

class obj {
  // world space transformations
  Matrix world_transform = identity(4);
  Matrix world_inverse = identity(4);

  // transformations applied in object space
  Matrix obj_transform = identity(4);
  Matrix obj_inverse = identity(4);

 public:

  // sets to a specific matrix
  void set_world_transform(const Matrix& m);
  // applies transformation to existing matrix
  void add_world_transform(const Matrix& m);
  // sets matrix to identity
  void clear_world_transform();

  void set_obj_transform(const Matrix& m);
  void add_obj_transform(const Matrix& m);
  void clear_obj_transform();

  Matrix get_world_transform() const;
  Matrix get_obj_transform() const;
  Matrix get_world_inverse() const;
  Matrix get_obj_inverse() const;

  // gives location in world space, returns a point
  tuple location() const;

  ray apply_transform(const ray& r) const;
  tuple apply_transform(const tuple& t) const;

  // assumed to be a point on the surface of the object
  virtual tuple normal_at(tuple p) const = 0;

  virtual std::vector<intersection> intersects(const ray& r) const = 0;
};

struct intersection {
  double t;
  const obj* o;
};

// vector from object to ray
tuple obj_to_ray(const obj& o, const ray& r);

const intersection NOINT{0, nullptr};

// given a vector of intersections between object and array, chooses the
// smallest non-negative time value that is returns the intersection which would
// be when the object "blocks" the ray
intersection hit(const std::vector<intersection>& hits);

#endif
