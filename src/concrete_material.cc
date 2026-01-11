#include "concrete_material.h"

striped::striped(const striped& s) : pattern_aggregate(s) { loop = s.loop; }
striped::striped(striped&& s) : pattern_aggregate(std::move(s)) {
  loop = s.loop;
}
striped& striped::operator=(const striped& s) {
  pattern_aggregate::operator=(s);
  loop = s.loop;
  
  return *this;
}
striped& striped::operator=(striped&& s) {
  pattern_aggregate::operator=(std::move(s));

  return *this;
}

color striped::pattern_at_local(tuple point) const {
  if (!loop) {
    if (std::floor(point.x) < 0) {
      return patterns.at(0)->pattern_at(point);
    } else if (std::floor(point.x) >= patterns.size()) {
      return patterns.at(patterns.size() - 1)->pattern_at(point);
    }
  }

  return patterns.at(abs(int(std::ceil(point.x)) % num_pats()))->pattern_at(point);
}

striped::striped(std::vector<color> c, bool loop)
    : pattern_aggregate{}, loop{loop} {
  for (auto it : c) {
    solid_color s{it};
    add_pat(s);
  }
}

std::unique_ptr<pattern> striped::clone() const {
  return std::make_unique<striped>(*this);
}

void striped::set_loop(bool b) { loop = b; }

color gradient::pattern_at_local(tuple point) const {
  double distance;

  // differentiating between ring and regular cases
  if (ring) {
    distance = norm(point - ORIGIN);
  } else {
    distance = point.x;
  }

  color c1 = patterns.at(std::abs(int(std::floor(distance)) % num_pats()))->pattern_at(point);
  color c2 = patterns.at(std::abs(int(std::ceil(distance)) % num_pats()))->pattern_at(point);

  // gradient equation
  if (loop) {
    return c1 + ((c2 - c1) * (distance - std::floor(distance)));
  } else {
    // non looping
    if (distance <= 0) {
      return patterns.at(0)->pattern_at(point);
    } else if (distance >= num_pats() - 1) {
      return patterns.at(num_pats() - 1)->pattern_at(point);
    } else {
      return c1 + ((c2 - c1) * (distance - std::floor(distance)));
    }
  }
}

gradient::gradient(std::vector<color> c, bool loop, bool ring)
    : pattern_aggregate{}, loop{loop}, ring{ring} {
  for (auto it : c) {
    solid_color s{it};
    add_pat(s);
  }
}

std::unique_ptr<pattern> gradient::clone() const {
  return std::make_unique<gradient>(*this);
}


void gradient::set_loop(bool b) { loop = b; }
void gradient::set_ring(bool r) { ring = r; }

checker::checker(std::vector<color> c) : pattern_aggregate{} {
  for (auto it : c) {
    solid_color s{it};
    add_pat(s);
  }
}
std::unique_ptr<pattern> checker::clone() const {
  return std::make_unique<checker>(*this);
}

color checker::pattern_at_local(tuple point) const {
  if (int(std::floor(point.x) + std::floor(point.y) + std::floor(point.z)) % 2 == 0) {
    return patterns.at(0)->pattern_at(point);
  } else {
    return patterns.at(1)->pattern_at(point);
  }
}
