#ifndef OBJ
#define OBJ

#include "render_obj.h"

class sphere final : public render_obj {
  tuple normal_at_local(tuple p) const override;
  std::vector<intersection> intersects_local(const ray& r) const override;

 public:
  ~sphere() = default;

  std::unique_ptr<render_obj> clone() const override;
  material mat_at(tuple p) const override;
};

class plane final : public render_obj {
  // because planes are 2D they essentially have a bright side and a dark side, based on the normal vectors, maybe worth changing
  tuple normal_at_local(tuple p) const override;
  std::vector<intersection> intersects_local(const ray& r) const override;

 public:
  ~plane() = default;

  std::unique_ptr<render_obj> clone() const override;
  material mat_at(tuple p) const override;
};

#endif
