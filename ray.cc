#include "ray.h"
#include <iostream>

obj::obj(tuple loc): location{loc} {}

void obj::set_transform(const Matrix& m) {
    transform = m * transform;
}

void obj::clear_transform() {
    transform = identity(4);
}

tuple ray::position(double t) const { return (direction * t) + origin; }

tuple obj_to_ray(const obj& o, const ray& r) {
  return r.origin - o.location;
}


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

