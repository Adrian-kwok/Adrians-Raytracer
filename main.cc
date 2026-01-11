#include <iomanip>
#include <iostream>

#include "canvas.h"
#include "light.h"
#include "matrix.h"
#include "matrix_transform.h"
#include "object.h"
#include "ray.h"
#include "tuples.h"
#include "world.h"
#include "concrete_material.h"

void display(Canvas& c) {
  int w, h;
  w = c.width();
  h = c.height();
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (c.pixel_at(j, i).r != 0) {
        std::cout << "█";
      } else {
        std::cout << " ";
      }
    }
    std::cout << std::endl;
  }
}

struct projectile {
  tuple pos;  // point
  tuple dir;  // vec
};

struct environment {
  tuple wind;  // vec
  tuple grav;  // vec
};

void tick(projectile& p, environment& e) {
  p.pos = p.pos + p.dir;
  p.dir = p.dir + e.wind + e.grav;
}

void p_point(const tuple& t) {
  std::cout << "(";
  for (int i = 0; i < 4; i++) {
    if (i) std::cout << ", ";
    std::cout << t.get(i);
  }
  std::cout << ")" << std::endl;
}

void p_mat(const Matrix& m) {
  std::cout << std::fixed << std::setprecision(5);

  for (int i = 0; i < m.num_rows(); i++) {
    std::cout << "|";
    for (int j = 0; j < m.num_cols(); j++) {
      if (m.get(i,j) >= 0) {
        std::cout << " ";
      }
      std::cout << m.get(i, j);
      std::cout << "|";
    }
    std::cout << std::endl;
  }
}

void p_color(const color& c) {
  std::cout << "(";
  std::cout << c.r << ", ";
  std::cout << c.g << ", ";
  std::cout << c.b;
  std::cout << ")" << std::endl;
}

void c_tuple(const tuple& t, Canvas& c) {
  c.write_pixel(round((c.width() / 2) - t.x), round((c.height() / 2) - t.z),
                color{1, 1, 1});
}

int main() {
  // Canvas c{180, 180};

  /*
  for (float i = 0; i < 1; i += 0.002) {
    projectile ball{point(0, 1, 0), vector(0.5, 3 * i, 0)};
    environment park{vector(0, 0, 0), vector(0, -0.02, 0)};

    while (ball.pos.y > 0) {
      tick(ball, park);
      tuple norm_dir = normalize(ball.dir);
      c.write_pixel(round(ball.pos.x), 180 - round(ball.pos.y),
                    color{float(norm_dir.x * 0.5 + 0.5),
                          float(norm_dir.y * 0.5 + 0.5), i});
    }
  }


  display(c);
  remove("./img/test.ppm");
  canvas_to_ppm(c, "./img/test.ppm");

  Canvas d{"./img/test.ppm"};
  remove("./img/test.ppm");
  canvas_to_ppm(d, "./img/test.ppm");

  Canvas e{Canvas{"./img/test.ppm"}};
  canvas_to_ppm(e, "./img/test.ppm");
*/

  /*
    Matrix m1{4, 4, "-4 2 -2 -3 9 6 2 6 0 -5 1 -5 0 0 0 0"}; // non invertible
    Matrix m2{4, 4, "-2 -8 3 5 -3 1 7 3 1 2 -9 6 -6 7 7 -9"}; // invertible

    tuple t{1,2,3,1};

    Matrix m3{4, 4, "1 2 3 4 2 4 4 2 8 6 4 1 0 0 0 1"};
    Matrix m4{4, 4, "-2 1 2 3 3 2 1 -1 4 3 6 5 1 2 7 8"};


    std::cout << det(m1) << std::endl;
    std::cout << det(m2) << std::endl;

    for (int i = 0; i < 4; i++) {
      std::cout << "| ";
      for (int j = 0; j < 4; j++) {
        std::cout << (m3 * m4).get(i, j) << " |";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;

    for (int i = 0; i < 4; i++) {
      std::cout << "| ";
      for (int j = 0; j < 4; j++) {
        std::cout << (m3 * identity(4)).get(i, j) << " |";
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << (m3 == m3) << std::endl; // true
    Matrix m5 {m3};

    std::cout << (m5 == m3) << std::endl; // true
    std::cout << (m4 == m5) << std::endl; // false

    Matrix m6 {m4 * m3};
    std::cout << (m6 == (m4 * m3)) << std::endl; // true
    for (int i = 0; i < 4; i++) {
      std::cout << (m3 * t).get(i) << std::endl;
    }
      */

  /*
  Matrix matt1 = translate(5, -3, 2);
  tuple p1 = point(-3, 4, 5);
  p_point(matt1 * p1);
  p_point(inverse(matt1) * p1);
  p_point(matt1 * vector(1, 1, 1));

  Matrix matt2 = scale(2, 3, 4);
  tuple p2 = point(-4, 6, 8);
  p_point(matt2 * p2);
  p_point(matt2 * vector(-4, 6, 8));
  p_point(inverse(matt2) * p2);
  p_point(scale(-1, 1, 1) * vector(2, 3, 4));

  Matrix mattx = roto_x(PI / 4);
  Matrix matty = roto_y(PI / 3);
  Matrix mattz = roto_z(PI / 2);
  tuple p3 = point(1, 0, 0);
  p_point(mattx * p3);
  p_point(matty * p3);
  p_point(mattz * p3);

  Matrix matshear = shear(1, 2, 3, 4, 5, 6);
  p_point(matshear * point(1, -2, 3));

  Canvas clock{50, 50};

  Matrix clock_rot = roto_y(PI / 6);
  tuple hand = point(0, 0, 20);
  for (int j = 0; j < 6; j++) {
    for (int i = 0; i < 12; i++) {
      c_tuple(shear(0,1,0,0,0,0) * scale(0.7, 0.7, 0.7) * hand, clock);
      hand = clock_rot * hand;
    }
    hand = scale(0.8, 0.8, 0.8) * hand;
    hand = roto_y(PI / 36) * hand;
  }

  tuple edge = point(0, 0, 23);
  Matrix edge_rot = roto_y(PI / 180);
  for (int i = 0; i < 360; i++) {
    c_tuple(shear(0,1,0,0,0,0) * (scale(0.7, 0.7, 0.7) * edge), clock);
    edge = edge_rot * edge;
  }

  canvas_to_ppm(clock, "./img/clock.ppm");
  */
  /*
  ray r{point(0, 0, -5), vector(0, 0, 1)};

  sphere s1{};
  sphere s2{1, point(1, 0, 0)};

  std::vector<intersection> intersect1 = s1.intersects(r);
  for (auto it : intersect1) {
    p_point(r.position(it.t));
  }

  std::vector<intersection> intersect2 = s2.intersects(r);
  for (auto it : intersect2) {
    p_point(r.position(it.t));
  }

  sphere s3{1, point(2, 2, 1)};
  std::vector<intersection> intersect3 = s3.intersects(r);
  for (auto it : intersect3) {
    p_point(r.position(it.t));
  }

  std::vector<intersection> hits;
  hits.emplace_back(intersection{1, &s1});
  hits.emplace_back(intersection{2, &s1});
  std::cout << hit(hits).t << std::endl;
  hits.clear();

  hits.emplace_back(intersection{1, &s1});
  hits.emplace_back(intersection{-1, &s1});
  std::cout << hit(hits).t << std::endl;
  hits.clear();

  hits.emplace_back(intersection{-2, &s1});
  hits.emplace_back(intersection{-1, &s1});
  std::cout << (hit(hits).o == NOINT.o) << std::endl;
  hits.clear();

  hits.emplace_back(intersection{5, &s1});
  hits.emplace_back(intersection{7, &s1});
  hits.emplace_back(intersection{-3, &s1});
  hits.emplace_back(intersection{2, &s1});
  std::cout << hit(hits).t << std::endl;
  hits.clear();
  */

  /*
  ray r{point(1, 2, 3), vector(0, 1, 0)};
  ray r2 = r.transform(translate(3,4,5));
  p_point(r2.origin);
  p_point(r2.direction);

  ray r3 = r.transform(scale(2, 3, 4));
  p_point(r3.origin);
  p_point(r3.direction);

  ray r4{point(0, 0, -5), vector(0, 0, 1)};
  sphere s;
  s.set_transform(scale(2,2,2));
  std::vector<intersection> hits = s.intersects(r4);
  std::cout << hits.size() << std::endl;
  std::cout << hits[0].t << std::endl;
  std::cout << hits[1].t << std::endl;

  s.clear_transform();
  s.set_transform(translate(5, 0, 0));
  std::vector<intersection> spits = s.intersects(r4);
  std::cout << spits.size() << std::endl;
  */
  // display(clock);

  /*
  sphere s;
  s.mat = material{color{0, 0.4, 1}, 0.1, 0.9, 0.9, 200};
  s.add_obj_transform(scale(1.5, 1.5, 1.5));
  sphere s2;
  s2.mat = material{color{0.9, 0.6, 0}, 0.1, 0.9, 0.9, 200};
  s2.add_world_transform(translate(0, 0, -3));
  s2.add_obj_transform(scale(0.25, 1.5, 1));

  point_light l{color{1.5, 1.5, 1.5}};
  l.set_world_transform(translate(5, 5, 0));

  Matrix rot = identity(4);
  const Matrix rot_const = roto_y(PI / 2);

  // stacking rotations
  //for (int i = 0; i < 315; i++) {rot = rot_const * rot;}

  for (double k = 0; k < 1; k++) {
    Canvas c{800, 800};
    s2.add_world_transform(roto_y(PI/2 + PI / 4));
    s2.add_obj_transform(roto_z(PI/4));
    for (double i = 0; i < 800; i++) {
      for (double j = 0; j < 800; j++) {
        ray r{point(j * -0.01 + 4.00, i * -0.01 + 4.00, -10), vector(0, 0, 1)};
        std::vector<intersection> hits = s.intersects(r);
        std::vector<intersection> temp = s2.intersects(r);
        hits.insert(hits.end(), temp.begin(), temp.end());
        if (hits.size() > 0) {
          if (hit(hits).o == &s) {
            // std::cout << "█";
            c.write_pixel(
                j, i,
                lighting(s.mat, l, r.position(hit(hits).t), r.direction,
                         s.normal_at(r.position(hit(hits).t))));
          } else {
            // std::cout << "#";
            c.write_pixel(
                j, i,
                lighting(s2.mat, l, r.position(hit(hits).t), r.direction,
                         s2.normal_at(r.position(hit(hits).t))));
          }
        } else {
          // std::cout << " ";
        }
      }
      // std::cout << std::endl;
    }

    canvas_to_ppm(c, std::string("img/sphere") + std::to_string(int(k)) +
  std::string(".ppm"));
    //rot = rot * rot_const;
  }
  */

  /*
  material m;
  tuple position = ORIGIN;

  //test 1
  tuple eyev = vector(0,0,-1);
  tuple normalv = vector(0,0, -1);
  point_light light{color{1,1,1}};
  light.set_world_transform(translate(0,0,-10));
  p_color(lighting(m,light,position,eyev,normalv));

  //test2
  eyev = vector(0, sqrt(2)/2, -sqrt(2)/2);
   p_color(lighting(m,light,position,eyev,normalv));

  //test 3
  eyev = vector(0,0,-1);
  light.set_world_transform(translate(0,10,-10));
  p_color(lighting(m,light,position,eyev,normalv));

  //test 4
  eyev = vector(0,-sqrt(2)/2, -sqrt(2)/2);
  p_color(lighting(m,light,position,eyev,normalv));

  //test 5
  eyev = vector(0,0,-1);
  light.set_world_transform(translate(0,0,10));
  p_color(lighting(m,light,position,eyev,normalv));

  */
  /*
    World w;
    w.add_light(std::unique_ptr<light>(new point_light{color{1,1,1}}));
    w.light_at(0).set_world_transform(translate(-10,10,-10));
    sphere s{};
    s.mat = material{color{0.8, 1.0, 0.6}, 0.1, 0.7, 0.2,200};
    w.add_obj(s);
    w.add_obj(sphere{});
    w.obj_at(1).set_obj_transform(scale(0.5,0.5,0.5));

    ray r {point(0,0,-5), vector(0,0,1)};
    p_color(w.color_at(r));
    std::vector<intersection> hits = w.intersect(r);
    for (auto it : hits) {
      std::cout << it.t << std::endl;
    }

    computation c{intersection{4, w.ptr_obj_at(0)}, r};
    std::cout << c.time << std::endl;
    std::cout << std::boolalpha << (c.o == w.ptr_obj_at(0)) << std::endl;
    std::cout << std::boolalpha << c.inside << std::endl;
    p_point(c.p);
    p_point(c.eyev);
    p_point(c.normalv);

    World w2;
    p_color(w2.color_at(r));
    p_color(w.color_at(r));
     p_color(w.color_at(ray{point(0,0,0.75), vector(0,0,-1)}));
  */

  std::cout << std::boolalpha << (identity(4) == view_transform(ORIGIN, point(0, 0, -1), vector(0, 1, 0))) << std::endl;
  p_mat(view_transform(ORIGIN, point(0, 0, -1), vector(0, 1, 0)));
  std::cout << std::boolalpha << (scale(-1, 1, -1) == view_transform(ORIGIN, point(0, 0, 1), vector(0, 1, 0))) << std::endl;
  std::cout << std::boolalpha << (translate(0, 0, -8) == view_transform(point(0, 0, 8), ORIGIN, vector(0, 1, 0))) << std::endl;

  p_mat(view_transform(point(1,3,2), point(4,-2,8),vector(1,1,0)));

  Camera c{160, 120, PI / 2};
  std::cout << c.get_hsize() << std::endl;
  std::cout << c.get_vsize() << std::endl;
  std::cout << c.get_fov() << std::endl;
  p_mat(c.get_transform());
  std::cout << Camera{200, 125, PI / 2}.get_pixel_size() << std::endl;
  std::cout << Camera{125, 200, PI / 2}.get_pixel_size() << std::endl;

  Camera c1{201, 101, PI /2};
  ray r1 = c1.ray_for_pixel(100, 50);
  p_point(r1.origin);
  p_point(r1.direction);

  ray r2 = c1.ray_for_pixel(0,0);
  p_point(r2.origin);
  p_point(r2.direction);

  c1.add_transform(roto_y(PI/4) * translate(0, -2, 5));
  ray r3 = c1.ray_for_pixel(100, 50);
  p_point(r3.origin);
  p_point(r3.direction);

  color o = color{0.1,0.1,0.1};
  color k = WHITE;
  striped good_luck{std::vector<color>{}};
  good_luck.add_obj_transform(roto_y(PI/2)); 
  striped s12{{k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k}};
  s12.add_obj_transform(roto_y(PI/2));
  good_luck.add_pat(s12); 
  striped s11{{k,o,k,o,k,o,o,k,k,o,o,k,k,o,o,o,k}};
  s11.add_obj_transform(roto_y(PI/2));
  good_luck.add_pat(s11);
  striped s8{{k,k,o,o,k,k,k,o,k,o,k,o,k,k,k,o,k}};
  s8.add_obj_transform(roto_y(PI/2));
  good_luck.add_pat(s8);
  striped s7{{k,o,k,o,k,o,o,k,k,o,k,o,k,k,k,o,k}};
  s7.add_obj_transform(roto_y(PI/2));
  good_luck.add_pat(s7);
  striped s9{{k,k,k,o,k,k,k,k,k,k,k,k,k,k,k,o,k}};
  s9.add_obj_transform(roto_y(PI/2));
  good_luck.add_pat(s9);
  striped s6{{k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k}};
  s6.add_obj_transform(roto_y(PI/2));
  good_luck.add_pat(s6); 
  striped s5{{k,o,o,k,k,k,o,k,k,k,o,k,k,o,o,k,k}};
  s5.add_obj_transform(roto_y(PI/2));
  good_luck.add_pat(s5);
  striped s4{{k,o,k,o,k,o,k,o,k,o,k,o,k,o,k,o,k}};
  s4.add_obj_transform(roto_y(PI/2));
  good_luck.add_pat(s4);
  striped s3{{k,o,o,k,k,k,o,k,k,k,o,k,k,k,k,o,k}};
  s3.add_obj_transform(roto_y(PI/2));
  good_luck.add_pat(s3);
  striped s2{{k,o,k,k,k,k,k,k,k,k,k,k,k,o,o,k,k}};
  s2.add_obj_transform(roto_y(PI/2));
  good_luck.add_pat(s2);
  striped s1{{k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k,k}};
  s1.add_obj_transform(roto_y(PI/2));
  good_luck.add_pat(s1);
  
  std::cout << good_luck.num_pats() << std::endl;

  good_luck.set_loop(false);

  good_luck.add_obj_transform(roto_x(PI));
  good_luck.add_obj_transform(scale(0.2,0.2,0.2));
  good_luck.add_world_transform(translate(-2,0,1.1));

  World w;
  point_light p {color {0.6,0.6,0.6}};
  p.add_world_transform(translate(-10,100,-20));
  w.add_light(p);

  point_light q {color {0.8, 0.8,0.8}};
  q.add_world_transform(translate(5, 1, 2));
  w.add_light(q);

  plane floor;
  floor.mat = material{color{1, 1, 1}};
  floor.mat.set_specular(0);
  
  plane left_wall = floor;
  left_wall.add_world_transform(translate(0,0,5) * roto_y(-PI/4) * roto_x(-PI / 2));
  left_wall.mat.set_color_pattern(good_luck);
  w.add_obj(left_wall);

  plane right_wall = floor;
  floor.mat.set_color_pattern(striped(std::vector<color>{{0.7,0.7,1},{1,1,1}}, true));
  right_wall.add_world_transform(translate(0,0,5) * roto_x(-PI / 2));
  w.add_obj(right_wall);
  w.add_obj(floor);

  sphere right;
  right.set_world_transform(translate(1.5,0.5,-0.5));
  right.set_obj_transform(scale(0.5,0.5,0.5));
  checker ch {{color{1,0,0}, color{1,1,0}}};
  ch.add_obj_transform(scale(0.4,0.4,0.4));
  right.mat.set_color_pattern(ch);
  right.mat.set_diffuse(0.7);
  right.mat.set_specular(1);
  right.mat.set_shininess(900);
  w.add_obj(right);

  sphere middle;
  middle.add_world_transform(scale(1,1,1));
  middle.add_obj_transform(roto_y(PI/6));
  middle.add_obj_transform(roto_z(PI/3));
  middle.add_world_transform(translate(0, 1, 0.5));
  gradient s {{color{0,0,0},BLACK,color{1,1,0},color{1,1,0}}, true, false};
  s.add_world_transform(translate(0.5,0.5,0));
  s.add_obj_transform(scale(0.1,0.1,0.1));
  middle.mat.set_color_pattern(s);
  middle.mat.set_diffuse(0.7);
  middle.mat.set_specular(0.4);
  w.add_obj(middle);

  sphere left;
  left.set_world_transform(translate(-1.5, 0.33, -0.75));
  left.set_obj_transform(scale(0.33,0.33,0.33));
  left.mat.set_color_pattern(solid_color{color{0.3, 0.9, 0.1}});
  left.mat.set_diffuse(0.8);
  left.mat.set_specular(1);
  w.add_obj(left);

  Camera cam{1920, 1080, PI/3 + 0.1};
  cam.set_transform(view_transform(point(0,1.5, -5), point(0, 1,0), vector(0,1,0)));

  canvas_to_ppm(cam.render(w), "img/aaa.ppm");
  /*
 point_light l {color{1,1,1}};
 l.add_world_transform(translate(0,0,-10));

  p_color(lighting(material{}, l,ORIGIN, vector(0,0,-1),vector(0,0,-1), true));

  // the shadow calculations need testing

  point_light regular {color{1,1,1}};
  regular.set_world_transform(translate(-10,10,-10));

  World w1;
  w1.add_light(regular);
  std::cout << w1.inShadow(0,point(0, 10, 0)) << std::endl;

  sphere s;
  w1.add_obj(s);

  std::cout << w1.inShadow(0,point(10, -10, 10)) << std::endl;
  std::cout << w1.inShadow(0,point(10, -10, 10) * -2) << std::endl;
  std::cout << w1.inShadow(0,point(-2, 2, -2)) << std::endl;

  */

  }


