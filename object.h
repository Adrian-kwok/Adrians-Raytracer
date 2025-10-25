#ifndef OBJ
#define OBJ

#include "tuples.h"
#include "ray.h"

struct sphere : public obj {
    std::vector<intersection> intersects(const ray& r) const override;
    tuple normal_at(tuple p) const override;
};



#endif
