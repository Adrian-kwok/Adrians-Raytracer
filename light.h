#ifndef LIGHT
#define LIGHT

#include "ray.h"

struct light : public obj {
  virtual ~light() = default;

  virtual color intensity() const = 0;

  // creates a unique pointer to a clone of the object
  virtual std::unique_ptr<light> clone() const = 0;

  // returns a normalized vector
  virtual tuple light_vec(tuple posn) const = 0;
};

// should make this in a separate module when new lights are added
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
