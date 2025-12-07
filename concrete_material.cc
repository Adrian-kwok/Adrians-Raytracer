#include "concrete_material.h"

color striped::pattern_at_local(tuple point) const {
  return colors.at(int(std::floor(point.x)) % colors.size());
}

striped::striped(std::vector<color> c) : pattern{}, colors{c} {}

std::unique_ptr<pattern> striped::clone() const {
  return std::make_unique<striped>(*this);
}

const std::vector<color>& striped::get_colors() const { return colors; }

void striped::set_colors(const std::vector<color>& c) { colors = c; }
void striped::set_colors(std::vector<color>&& c) { std::swap(colors, c); }

color gradient::pattern_at_local(tuple point) const {
  double distance;
  
  // differentiating between ring and regular cases
  if (ring) {
    distance = norm(point - ORIGIN);
  } else {
    distance = point.x;
  }

  color c1 = colors.at(int(std::floor(distance)) % colors.size());
  color c2 = colors.at(int(std::ceil(distance)) % colors.size());

  // gradient equation
  if (loop) {
    return c1 + ((c2 - c1) * (distance - std::floor(distance)));
  } else {
    // non looping
    if (distance <= 0) {
      return colors.at(0);
    } else if (distance >= colors.size() - 1) {
      return colors.at(colors.size() - 1);
    } else {
      return c1 + ((c2 - c1) * (distance - std::floor(distance)));
    }
  }
}

gradient::gradient(std::vector<color> c, bool loop, bool ring) : colors{c}, loop{loop}, ring{ring} {}

std::unique_ptr<pattern> gradient::clone() const {
  return std::make_unique<gradient>(*this);
}

const std::vector<color>& gradient::get_colors() const { return colors; }

void gradient::set_colors(const std::vector<color>& c) { colors = c; }
void gradient::set_colors(std::vector<color>&& c) { std::swap(colors, c); }
void gradient::set_loop(bool b) {loop = b;}
void gradient::set_ring(bool r) {ring = r;}
