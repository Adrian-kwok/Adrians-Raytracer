#include "world.h"

#include <utility>

//
World::World() {}

World::World(const World& other) {
  for (size_t i = 0; i < other.lights.size(); i++) {
    lights.emplace_back(other.lights.at(i) != nullptr ? other.lights.at(i)->clone()
                                               : nullptr);
  }

  for (size_t i = 0; i < other.objs.size(); i++) {
    objs.emplace_back(other.objs.at(i) != nullptr ? other.objs.at(i)->clone()
                                               : nullptr);
  }
}

World::World(World&& other)
    : lights{std::move(other.lights)}, objs{std::move(other.objs)} {}

World& World::operator=(const World& other) {
  if (this == &other) return *this;

  // copy-swap idiom
  World temp{other};
  std::swap(objs, temp.objs);
  std::swap(lights, temp.lights);

  return *this;
}

World& World::operator=(World&& other) {
  if (this == &other) return *this;  // perhaps?

  std::swap(objs, other.objs);
  std::swap(lights, other.lights);

  return *this;
}

void World::add_obj(std::unique_ptr<render_obj> o) {
  objs.emplace_back(std::move(o));
}

void World::add_obj(const render_obj& o) { add_obj(o.clone()); }

// hopefully it was checked that the index is within bounds...
render_obj& World::obj_at(int i) { return *objs.at(i); }
render_obj* World::ptr_obj_at(int i) { return objs.at(i).get(); }

void World::delete_obj_at(int i) {
  // o(n), unlikely operation however.
  if (i >= 0 && i < objs.size()) {
    objs.erase(objs.begin() + i);
  }
}

int World::num_obj() const { return objs.size(); }

std::vector<intersection> World::intersect(const ray& r) const {
  std::vector<intersection> hits;

  for (int i = 0; i < objs.size(); i++) {
    std::vector<intersection> temp = objs.at(i)->intersects(r);
    hits.insert(hits.end(), temp.begin(), temp.end());
  }

  // lambda used to sort the elements
  std::sort(hits.begin(), hits.end(),
            [](intersection a, intersection b) { return a.t < b.t; });

  return hits;
}

void World::add_light(std::unique_ptr<light> other_light) {
  lights.emplace_back(std::move(other_light));
}

void World::add_light(const light& l) { add_light(l.clone()); }

light& World::light_at(int i) { return *lights.at(i); }
light* World::ptr_light_at(int i) { return lights.at(i).get(); }

void World::delete_light_at(int i) {
  // o(n), unlikely operation however.
  if (i >= 0 && i < lights.size()) {
    lights.erase(lights.begin() + i);
  }
}

int World::num_light() const {return lights.size();}

color World::shade_hit(const computation& c) const{
  color result = BLACK;
  for (int i = 0; i < lights.size(); i++) {
    result = result + lighting(c.o->mat_at(c.p), *lights[i], c.p, c.eyev, c.normalv);
  }
  return result;
}

color World::color_at(const ray& r) const {
  std::vector<intersection> hits = intersect(r);
  
  if (hits.size() == 0) { // use the background color
    return background_col();
  } else {  // use the rendered color
    computation c {hit(hits), r};
    return shade_hit(c);
  }
}

color World::background_col() const {
  return bg;
}
