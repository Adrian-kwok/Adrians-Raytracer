#ifndef RAY
#define RAY

#include <vector>
#include <memory>

#include "color.h"
#include "matrix_transform.h"

struct intersection;

struct ray {
  tuple origin = ORIGIN;              // should be a point!
  tuple direction = vector(1, 0, 0);  // should be a vector!

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
};

struct intersection {
  double t;
  const obj* o;
};

// used with render objects
struct material {
  color c = color{1, 1, 1};
  float ambient = 0.1;
  float diffuse = 0.5;
  float specular = 1;
  float shininess = 200.0;
};

// vector from object to ray
tuple obj_to_ray(const obj& o, const ray& r);

const intersection NOINT{0, nullptr};

// given a vector of intersections between object and array, chooses the
// smallest non-negative time value that is returns the intersection which would
// be when the object "blocks" the ray
intersection hit(const std::vector<intersection>& hits);

struct light;

// lighting function, should eventually be changed from point
// light to just a general light abstract base class
// position is a point, eye and normal are vectors
color lighting(const material& m, const light& l, const tuple& position,
               const tuple& eye, const tuple& normal);

// object to be rendered
class render_obj : public obj {
 public:
  // probably (maybe?) should add virtual big 5 when needed
  // assumed to be a point on the surface of the object
  virtual tuple normal_at(tuple p) const = 0;

  virtual std::vector<intersection> intersects(const ray& r) const = 0;
};

struct light : public obj {
  virtual color intensity() const = 0;

  // returns a normalized vector
  virtual tuple light_vec(tuple posn) const = 0;
};

#endif
