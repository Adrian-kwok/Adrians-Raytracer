#include "material.h"

color pattern::pattern_at(tuple point) const {
  point = apply_transform(point);

  return pattern_at_local(point);
}

material::material(color c) : color_pattern{std::make_unique<solid_color>(c)} {}

material::material(const pattern& p, float ambient, float diffuse,
                   float specular, float shininess)
    : color_pattern{p.clone()},
      ambient{ambient},
      diffuse{diffuse},
      specular{specular},
      shininess{shininess} {}

material::material(const material& m)
    : color_pattern{m.color_pattern->clone()},
      ambient{m.ambient},
      diffuse{m.diffuse},
      specular{m.specular},
      shininess{m.shininess} {}

material& material::operator=(const material& m) {
  material temp{m};
  color_pattern = std::move(temp.color_pattern);
  ambient = temp.ambient;
  diffuse = temp.diffuse;
  specular = temp.specular;
  shininess = temp.shininess;
  return *this;
}

material::material(material&& m)
    : color_pattern{std::move(m.color_pattern)},
      ambient{m.ambient},
      diffuse{m.diffuse},
      specular{m.specular},
      shininess{m.shininess} {}

material& material::operator=(material&& m) {
  std::swap(color_pattern, m.color_pattern);
  std::swap(ambient, m.ambient);
  std::swap(diffuse, m.diffuse);
  std::swap(specular, m.specular);
  std::swap(shininess, m.shininess);

  return *this;
}

void material::set_color_pattern(const pattern& p) {
  color_pattern = std::move(p.clone());
}

void material::set_ambient(const float& a) {ambient = a;}
void material::set_diffuse(const float& d) {diffuse = d;}
void material::set_specular(const float& sp) {specular = sp;}
void material::set_shininess(const float& sh) {shininess = sh;}

const pattern& material::get_color_pattern() const {
  return *color_pattern;
}
const float& material::get_ambient() const {return ambient;}
const float& material::get_diffuse() const {return diffuse;}
const float& material::get_specular() const {return specular;}
const float& material::get_shininess() const {return shininess;}

solid_color::solid_color(color c)
    : pattern{}, c{c} {}

std::unique_ptr<pattern> solid_color::clone() const {
  return std::make_unique<solid_color> (*this);
}

void solid_color::set_color(color col) {
  c = col;
}

color solid_color::pattern_at_local(tuple point) const {
  return c;
}
