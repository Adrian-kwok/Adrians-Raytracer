#include "render_obj.h"

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
               const tuple& eye, const tuple& normal, bool in_shadow, const tuple& local_position) {
  color ambient;
  color diffuse = BLACK;   // default
  color specular = BLACK;  // ""

  // combine the surface color with the light's color
  // here the position is adjusted for the 
  color effective = m.get_color_pattern().pattern_at(local_position) * l.intensity();
  // direction to light source
  tuple lightvec = l.light_vec(position);
  ambient = effective * m.get_ambient();

  // Case for shadows
  if (in_shadow) {
    return ambient;
  }

  // cosine of angle between light and normal, if negative then light is on the
  // other side
  double light_dot_normal = dot(lightvec, normal);
  if (light_dot_normal >= 0) {
    diffuse = effective * m.get_diffuse() * light_dot_normal;

    // how close is the eye vector to ideal reflection?
    // eye is negative here because it just needs to work with the world class
    double reflect_dot_eye = dot(reflect(lightvec, normal), -eye);
    if (reflect_dot_eye > 0) {
      // compute specular contribution
      specular = l.intensity() * m.get_specular() * pow(reflect_dot_eye, m.get_shininess());
    }
  }

  // return ambient + diffuse + specular;
  return ambient + diffuse + specular;
}

computation::computation(const intersection& i, const ray& r)
    : time{i.t},
      o{i.o},
      p{r.position(i.t)},
      eyev{-r.direction},
      normalv{i.o->normal_at(p)},
      inside{false}, 
      local{i.o->apply_transform(p)}{

  // before we maybe fix the normal vector, we calculate the offset normal
  // if normal maps are implemented, should this be changed to be a strictly geometric normal? unsure
  offset_p = p + normalv * EPSILON;
  
  if (dot(normalv, eyev) < 0) {
    inside = true;
    normalv = -normalv;
  }
}

render_obj::render_obj(): obj{} {}

tuple render_obj::normal_at(tuple p) const {
  if (p.w != 1) std::cerr << "not a point, error" << std::endl;
  p = apply_transform(p);

  tuple object_norm = normal_at_local(p);  // object space normal

  object_norm = transpose(get_world_inverse() * get_obj_inverse()) * object_norm;
  object_norm.w = 0;
  return normalize(object_norm);  // back to world space
}


std::vector<intersection> render_obj::intersects(const ray& r) const {
  return intersects_local(apply_transform(r));
}
