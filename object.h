#ifndef OBJ
#define OBJ

#include "tuples.h"
#include "ray.h"

struct sphere : public obj {
    double radius;
    std::vector<intersection> intersects(const ray& r) const override;
    sphere(double r = 1, tuple loc = ORIGIN);
};



#endif
