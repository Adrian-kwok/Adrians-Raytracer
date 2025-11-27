#include "object.h"

const int BASERAD = 1;

double determinant(double a, double b, double c) {
  return pow(b, 2) - 4 * a * c;
}

std::unique_ptr<render_obj> sphere::clone() const {
  return std::unique_ptr<sphere>(new sphere{*this});
}

std::vector<intersection> sphere::intersects_local(const ray& r) const {
  tuple s2r = r.origin - ORIGIN;

  // variables of the quadratic formula
  double a = dot(r.direction, r.direction);
  double b = 2 * dot(s2r, r.direction);
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
tuple sphere::normal_at_local(tuple p) const {
  return p - ORIGIN;  // object space normal
}

material sphere::mat_at(tuple p) const { return mat; }

std::unique_ptr<render_obj> plane::clone() const {
  return std::unique_ptr<plane>(new plane{*this});
}

std::vector<intersection> plane::intersects_local(const ray& r) const {
  if (absolute(r.direction.y) < EPSILON) {  //  parallel case
    return std::vector<intersection>{};
  } else {  // solving for when ray intersects the xz plane (default plane)
    return std::vector<intersection>{
        intersection{-(r.origin.y / r.direction.y), this}};
  }
}

tuple plane::normal_at_local(tuple p) const {
  return tuple{0,1,0}; // default plane is assumed to be the XZ plane
}

material plane::mat_at(tuple p) const {
  return mat;
}
