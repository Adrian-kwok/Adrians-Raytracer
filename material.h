#ifndef MAT
#define MAT

#include "ray.h"
#include <algorithm>

class pattern : public obj {
  virtual color pattern_at_local(tuple point) const = 0;

 public:
  // if used for an object, expects that transformations have already been
  // applied to have this in "local space"
  color pattern_at(tuple point) const;

  virtual std::unique_ptr<pattern> clone() const = 0;

  virtual ~pattern() = default;
};

// although this is a concrete class it's useful for creating defaults
class solid_color : public pattern {
  color c;

  color pattern_at_local(tuple point) const override;

 public:
  solid_color(color c);

  std::unique_ptr<pattern> clone() const override;

  void set_color(color c);

  ~solid_color() = default;
};

class material {
  std::unique_ptr<pattern> color_pattern;
  float ambient = 0.1;
  float diffuse = 0.7;
  float specular = 0.9;
  float shininess = 200.0;

  public:

  material(color c = color{1,1,1});
  material(const pattern& p, float ambient, float diffuse, float specular,
           float shininess);

  // big 5 to work with unique ptr
  material(const material& m);
  material& operator=(const material& m);
  material(material&& m);
  material& operator=(material&& m);
  ~material() = default;

  void set_color_pattern(const pattern& p);
  void set_ambient(const float& a);
  void set_diffuse(const float& d);
  void set_specular(const float& sp);
  void set_shininess(const float& sh);

  const pattern& get_color_pattern() const;
  const float& get_ambient() const;
  const float& get_diffuse() const;
  const float& get_specular() const;
  const float& get_shininess() const;
};

#endif
