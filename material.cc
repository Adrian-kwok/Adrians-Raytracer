#include "material.h"

color pattern::pattern_at(tuple point) const {
  if (!use_global) {
    point = apply_transform(point);
  }

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
pattern& material::get_color_pattern() {return *color_pattern;}
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

pattern_aggregate::pattern_aggregate(): patterns{} {}
pattern_aggregate::pattern_aggregate(const pattern_aggregate& other): pattern{other}, patterns{} {
  for(int i = 0; i < other.num_pats(); i++) {
    add_pat(*other.patterns.at(i));
  }
}
pattern_aggregate::pattern_aggregate(pattern_aggregate&& other): pattern{other}, patterns{} {
  std::swap(patterns, other.patterns);
}
pattern_aggregate& pattern_aggregate::operator=(const pattern_aggregate& other) {
  // copy swap idiom can't be used here since pattern_aggregate is abstract
  // this is a cool technicality in C++!
  pattern::operator=(other);

  patterns.clear();
  for(int i = 0; i < other.num_pats(); i++) {
    add_pat(*other.patterns.at(i));
  }

  return *this;
}
pattern_aggregate& pattern_aggregate::operator=(pattern_aggregate&& other) {
  pattern::operator=(std::move(other));

  std::swap(patterns, other.patterns);
  return *this;
}

void pattern_aggregate::add_pat(pattern& p) {
  patterns.emplace_back(p.clone());
}

void pattern_aggregate::add_pat(pattern&& p) {
  add_pat(p);
}

pattern& pattern_aggregate::get_pat(int i) {
  return *patterns.at(i);
}
pattern* pattern_aggregate::ptr_get_pat(int i) {
  return patterns.at(i).get();
}
int pattern_aggregate::num_pats() const {
  return patterns.size();
}

void pattern::set_global(bool g) {
  use_global = g;
}

