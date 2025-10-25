#include "ray.h"

#include <iostream>

void obj::set_world_transform(const Matrix& m) {
  world_transform = m;
  world_inverse = inverse(world_transform);
}

void obj::add_world_transform(const Matrix& m) {
  world_transform = m * world_transform;
  world_inverse = inverse(world_transform);
}

void obj::clear_world_transform() {
  world_transform = identity(4);
  world_inverse = identity(4);
}

void obj::set_obj_transform(const Matrix& m) {
  obj_transform = m * obj_transform;
  obj_inverse = inverse(obj_transform);
}

void obj::add_obj_transform(const Matrix& m) {
  obj_transform = m * obj_transform;
  obj_inverse = inverse(obj_transform);
}


void obj::clear_obj_transform() {
  obj_transform = identity(4);
  obj_inverse = identity(4);
}

tuple obj::location() const { return world_transform * ORIGIN; }

ray obj::apply_transform(const ray& r) const {
  ray rmod = r;
  rmod.origin = apply_transform(r.origin);
  rmod.direction = apply_transform(r.direction);
  return rmod;
}

tuple obj::apply_transform(const tuple& t) const {
  tuple tmod = t;
  tmod = world_inverse * tmod;
  tmod = obj_inverse * tmod;
  return tmod;
}

tuple ray::position(double t) const { return (direction * t) + origin; }

tuple obj_to_ray(const obj& o, const ray& r) { return r.origin - o.location(); }

intersection hit(const std::vector<intersection>& hits) {
  intersection result = NOINT;
  for (auto it : hits) {
    if (it.t >= 0 && (it.t <= result.t || result.o == nullptr)) {
      result = it;
    }
  }
  return result;
}

ray ray::transform(const Matrix& m) const {
  return ray{m * origin, m * direction};
}
