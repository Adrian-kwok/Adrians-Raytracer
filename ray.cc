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
  obj_transform = m;
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

Matrix obj::get_world_transform() const { return world_transform; }
Matrix obj::get_obj_transform() const { return obj_transform; }
Matrix obj::get_world_inverse() const { return world_inverse; }
Matrix obj::get_obj_inverse() const { return obj_inverse; }

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

// produces reflection across that normal
tuple ray::reflect(const tuple& normal) const {
  return direction - normal * 2 * dot(direction, normal);
}

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

color lighting(const material& m, const light& l, const tuple& position,
               const tuple& eye, const tuple& normal) {
  color ambient;
  color diffuse = BLACK;   // default
  color specular = BLACK;  // ""

  // combine the surface color with the light's color
  color effective = m.c * l.intensity();
  // direction to light source
  tuple lightvec = l.light_vec(position);
  ambient = effective * m.ambient;

  // cosine of angle between light and normal, if negative then light is on the
  // other side
  double light_dot_normal = dot(lightvec, normal);
  if (light_dot_normal >= 0) {
    diffuse = effective * m.diffuse * light_dot_normal;

    // how close is the eye vector to ideal reflection?
    double reflect_dot_eye = dot(reflect(lightvec, normal), eye);
    if (reflect_dot_eye > 0) {
      // compute specular contribution
      specular = l.intensity() * m.specular *
                 pow(reflect_dot_eye, m.shininess);
    }
  }

  //return ambient + diffuse + specular;
  return ambient + diffuse + specular;
}
