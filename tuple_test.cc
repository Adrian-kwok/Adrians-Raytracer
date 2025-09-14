#include <iostream>

#include "canvas.h"
#include "tuples.h"

void display(Canvas& c) {
  int w, h;
  w = c.width();
  h = c.height();
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (c.pixel_at(j, i).r != 0) {
        std::cout << "*";
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

int main() {
  Canvas c{200, 100};

  projectile ball{point(0, 1, 0), normalize(vector(1, 12, 0)) * 0.8};
  environment park{vector(0.01, 0, 0), vector(0, -0.01, 0)};

  while (ball.pos.y > 0) {
    tick(ball, park);
    tuple norm_dir = normalize(ball.dir);
    c.write_pixel(round(ball.pos.x), 100 - round(ball.pos.y), color{float(norm_dir.x * 0.5 + 0.5), float(norm_dir.y * 0.5 + 0.5), 0});
  }

  display(c);
  remove("./img/test.ppm");
  canvas_to_ppm(c, "./img/test.ppm");
}
