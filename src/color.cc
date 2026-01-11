#include "color.h"

color operator+(color c1, color c2) {
  return color{c1.r + c2.r, c1.g + c2.g, c1.b + c2.b};
}
color operator-(color c1, color c2) {
  return color{c1.r - c2.r, c1.g - c2.g, c1.b - c2.b};
}
color operator-(color c) { return color{-c.r, -c.g, -c.b}; }

color operator*(color t, float scalar) {
  return color{t.r * scalar, t.g * scalar, t.b * scalar};
}

color operator*(color c1, color c2) {
    return color{c1.r * c2.r, c1.g * c2.g, c1.b * c2.b};
}

bool operator==(color c1, color c2) {
  return (equal(c1.r, c2.r) && equal(c1.g, c2.g) && equal(c1.b, c2.b));
}
