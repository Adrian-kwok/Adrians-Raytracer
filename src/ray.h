#ifndef RAY
#define RAY

#include <memory>
#include <vector>

#include "color.h"
#include "matrix_transform.h"

struct intersection;

struct ray {
  tuple origin = ORIGIN;              // should be a point!
  tuple direction = vector(1, 0, 0);  // should be a vector!

  // returns a point
  tuple position(double t) const;
  tuple reflect(const tuple& normal) const;
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

  protected:
  virtual ~obj() = 0;

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

  // converts to object space
  ray apply_transform(const ray& r) const;
  // converts to object space
  tuple apply_transform(const tuple& t) const;

  // perhaps consider a set of helper functions that convert from object space to world space?
};

#endif
