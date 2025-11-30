#ifndef RENDEROBJ
#define RENDEROBJ

#include "light.h"
#include "material.h"


struct render_obj;

struct intersection {
  double t;
  const render_obj* o;
};

const intersection NOINT{0, nullptr};

// given a vector of intersections between object and array, chooses the
// smallest non-negative time value that is returns the intersection which would
// be when the object "blocks" the ray
intersection hit(const std::vector<intersection>& hits);

// object to be rendered
class render_obj : public obj {
  virtual tuple normal_at_local(tuple p) const = 0;
  virtual std::vector<intersection> intersects_local(const ray& r) const = 0;
  
 public:
  // at some point there will be a need for polymorphic materials, be paitient
  material mat;

  // probably (maybe?) should add virtual big 5 when needed
  virtual ~render_obj() = default;

  // creates a unique pointer to a clone of the object
  virtual std::unique_ptr<render_obj> clone() const = 0;

  virtual material mat_at(tuple p) const = 0;

  // assumed to be a point on the surface of the object
  tuple normal_at(tuple p) const;

  std::vector<intersection> intersects(const ray& r) const;
};

struct computation {
  bool inside;
  double time;
  const render_obj* o;
  tuple p;
  tuple offset_p;
  tuple eyev;
  tuple normalv;

  computation(const intersection& i, const ray& r);
};

// lighting function, should eventually be changed from point
// light to just a general light abstract base class
// position is a point, eye and normal are vectors
color lighting(const material& m, const light& l, const tuple& position,
               const tuple& eye, const tuple& normal, bool in_shadow);

#endif

