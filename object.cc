#include "object.h"

const int BASERAD = 1;

double determinant(double a, double b, double c) {
  return pow(b, 2) - 4 * a * c;
}


std::vector<intersection> sphere::intersects(const ray& r) const {
  ray rmod = apply_transform(r);

  tuple s2r = rmod.origin - ORIGIN;

  // variables of the quadratic formula
  double a = dot(rmod.direction, rmod.direction);
  double b = 2 * dot(s2r, rmod.direction);
  double c = dot(s2r, s2r) - BASERAD;
  double det = determinant(a, b, c);

  if (det < 0) {
    return std::vector<intersection>{};
  } else {
    // quadratic formula
    return std::vector<intersection>{
        intersection{(-b + sqrt(det)) / (2 * a), this},
        intersection{(-b - sqrt(det)) / (2 * a), this}};
  }
}

// should be taking in a point
tuple sphere::normal_at(tuple p) const {
  if (p.w != 1) std::cerr << "not a point, error" << std::endl;
  p = apply_transform(p);

  tuple object_norm = normalize(p - ORIGIN);  // object space normal
  //object_norm = transpose(inverse(transform)) * object_norm;
  object_norm.w = 0;

  return normalize(object_norm);  // back to world space
}
