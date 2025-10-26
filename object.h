#ifndef OBJ
#define OBJ

#include "ray.h"

struct sphere : public render_obj {
  material mat;

  std::vector<intersection> intersects(const ray& r) const override;
  tuple normal_at(tuple p) const override;
};

#endif
