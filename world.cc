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
    // with this implementation, wouldn't the ambient lighting add up to an annoying degree? unsure
    result = result + lighting(c.o->mat_at(c.p), *lights[i], c.p, c.eyev, c.normalv, inShadow(i,c.offset_p));
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

Matrix view_transform(tuple from, tuple to, tuple up) {
  // creating vectors which serve as the new axis for the transformation
  tuple forward = normalize(to - from);
  tuple left = cross(forward, normalize(up));
  tuple true_up = cross(left, forward);

  // creating the transformation matrix
  Matrix orientation = identity(TUPLE_SIZE);

  orientation.set(0,0,left.x);
  orientation.set(0,1,left.y);
  orientation.set(0,2,left.z);
  orientation.set(1,0,true_up.x);
  orientation.set(1,1,true_up.y);
  orientation.set(1,2,true_up.z);
  orientation.set(2,0,-forward.x);
  orientation.set(2,1,-forward.y);
  orientation.set(2,2,-forward.z);

  return orientation * translate(-from.x, -from.y, -from.z);
}

void Camera::update_pixel_size() {
  // calculations assume that the canvas is 1 unit away from the camera
  double half_view = tan(fov / 2);
  double aspect = double(hsize) / double(vsize);
  
  half_width = aspect >= 1 ? half_view : half_view * aspect;
  half_height = aspect >= 1 ? half_view / aspect : half_view;

  pixel_size = (half_width * 2) / hsize;
}

Camera::Camera(int h, int v, double fov): hsize{h}, vsize{v}, fov{fov} {
  update_pixel_size();
}
int Camera::get_hsize() const {return hsize;}
int Camera::get_vsize() const {return vsize;}
double Camera::get_fov() const {return fov;}
double Camera::get_pixel_size() const {return pixel_size;}
const Matrix & Camera::get_transform() const {return transform;}

void Camera::set_hsize(int h) {
  hsize = h;
  update_pixel_size();
}

void Camera::set_vsize(int v) {
  vsize = v;
  update_pixel_size();
}

void Camera::set_fov(double new_fov) {
  fov = new_fov;
  update_pixel_size();
}

void Camera::set_transform(const Matrix& m) {
  transform = m;
  inverse_transform = inverse(transform);
}

void Camera::set_transform(Matrix&& m) {
  std::swap(transform, m);
  inverse_transform = inverse(transform);
}

void Camera::add_transform(const Matrix& m) {
  transform = m * transform;
  inverse_transform = inverse(transform);
}

ray Camera::ray_for_pixel(int x, int y) const {
  // 0.5 is used to get the center of a pixel for a ray to hit
  double world_x = half_width - ((x + 0.5) * pixel_size);
  double world_y = half_height - ((y + 0.5) * pixel_size);

  // canvas is taken to be at z = -1
  tuple pixel = inverse_transform * point(world_x, world_y, -1);
  tuple origin = inverse_transform * ORIGIN;
  pixel.w = 1;// oops!
  origin.w = 1;
  return ray{origin, normalize(pixel - origin)};
}

Canvas Camera::render(const World& w) const {
  Canvas image {hsize, vsize};

  for (int y = 0; y < vsize; y++) {
    for (int x = 0; x < hsize; x++) {
      image.write_pixel(x,y,w.color_at(ray_for_pixel(x,y)));
    }
  }

  return image;
}

bool World::inShadow(int lightind, tuple pt) const {

  tuple lightvec  = pt - lights.at(lightind)->location();

  ray lightray {lights.at(lightind)->location(), normalize(lightvec)};
  intersection i = hit(intersect(lightray));

  return i.o != nullptr && i.t < norm(lightvec);
}
