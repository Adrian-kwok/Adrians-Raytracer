#include "ray.h"

#ifndef LIGHT
#define LIGHT

// this is temporary and should be replaced with an abc
// for which different types of lights derive themselves from
class point_light : public light {
  color light_col;

 public:
  ~point_light() = default;
  point_light(color c);

  // creates a unique pointer to a clone of the object
  std::unique_ptr<light> clone() const override;
  color intensity() const override;
  tuple light_vec(tuple posn) const override;
};
#endif
