#include "ray.h"

#ifndef LIGHT
#define LIGHT

// this is temporary and should be replaced with an abc
// for which different types of lights derive themselves from
class point_light : public light {
  color light_col;

  public:
    point_light(color c);
    color intensity() const override;
    tuple light_vec(tuple posn) const override;
};
#endif
