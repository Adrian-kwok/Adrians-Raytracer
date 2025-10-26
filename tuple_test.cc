#include <iostream>

#include "light.h"
#include "canvas.h"
#include "matrix.h"
#include "matrix_transform.h"
#include "object.h"
#include "ray.h"
#include "tuples.h"

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

  sphere s;
  s.mat = material{color{0.2,.7,0}, 0.1, 0.9, 0.9, 200};
  s.add_obj_transform(scale(1.5, 1.5, 1.5));
  sphere s2;
  s2.mat = material{color{0.4,0.1,1}, 0.1, 0.9, 0.9, 200};
  s2.add_world_transform(translate(0, 0, -2));
  s2.add_obj_transform(scale(0.25, 1.5, 1));
  s2.add_obj_transform(roto_z(PI / 4));

  point_light l{color{1.5,1.5,1.5}};
  l.set_world_transform(translate(4,5,0));

  Matrix rot = identity(4);
  const Matrix rot_const = roto_y(PI / 180);
  for (double k = 0; k < 360; k++) {
     Canvas c{200, 200};
    for (double i = 0; i < 200; i++) {
      for (double j = 0; j < 200; j++) {
        ray r{point(j * -0.04 + 4.00,i * -0.04 + 4.00, -10), vector(0, 0, 1)};
        r.origin = rot * r.origin;
        r.direction = normalize(rot * r.direction); 
        std::vector<intersection> hits = s.intersects(r);
        std::vector<intersection> temp = s2.intersects(r);
        hits.insert(hits.end(), temp.begin(), temp.end());
        if (hits.size() > 0) {
          if (hit(hits).o == &s) {
            //std::cout << "█";
            c.write_pixel(j, i, lighting(s.mat, l, r.position(hit(hits).t), r.direction, s.normal_at(r.position(hit(hits).t))));
          } else {
            //std::cout << "#";
            c.write_pixel(j, i, lighting(s2.mat, l, r.position(hit(hits).t), r.direction, s2.normal_at(r.position(hit(hits).t))));
          }
        } else {
          //std::cout << " ";
        }
      }
      //std::cout << std::endl;
    }
    
    canvas_to_ppm(c, std::string("img/sphere") + std::to_string(int (k + 20)) + std::string(".ppm"));
    rot = rot * rot_const;
  }


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

}
