#ifndef OBJ
#define OBJ

#include "ray.h"

class sphere final : public render_obj {
  tuple normal_at_local(tuple p) const override;

 public:
  material mat;

  ~sphere() = default;

  std::unique_ptr<render_obj> clone() const override;
  std::vector<intersection> intersects(const ray& r) const override;
  material mat_at(tuple p) const override;
};

#endif
