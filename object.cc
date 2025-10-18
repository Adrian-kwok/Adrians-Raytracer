#include "object.h"

double determinant(double a, double b, double c) {
  return pow(b, 2) - 4 * a * c;
}
 
sphere::sphere(double r, tuple loc): obj{loc}, radius{r} {}


std::vector<intersection> sphere::intersects(const ray& r) const {
  ray rmod = r.transform(inverse(transform));
  tuple s2r = obj_to_ray(*this, rmod);

  // variables of the quadratic formula
  double a = dot(rmod.direction, rmod.direction);
  double b = 2 * dot(s2r, rmod.direction);
  double c = dot(s2r, s2r) - radius;
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
