#include <iostream>

#include "canvas.h"
#include "tuples.h"

void display(Canvas& c) {
  int w, h;
  w = c.width();
  h = c.height();
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      std::cout << c.pixel_at(j, i).r << " ";
    }
    std::cout << std::endl;
  }
}

int main() {
  Canvas c{10, 10};
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if ((i + j) % 3) {
        c.write_pixel(i, j, color{1, 0, 0});
      } else {
        c.write_pixel(i, j, color{0, 0, 0});
      }
    }
  }
  display(c);
}
