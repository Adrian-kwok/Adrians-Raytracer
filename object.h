#ifndef OBJ
#define OBJ

#include "ray.h"

struct sphere : public render_obj {
  material mat;

  ~sphere() = default;

  std::unique_ptr<render_obj> clone() const override;
  std::vector<intersection> intersects(const ray& r) const override;
  tuple normal_at(tuple p) const override;
  material mat_at(tuple p) const override;
};

#endif
