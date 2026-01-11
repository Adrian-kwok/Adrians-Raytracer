#ifndef COLOR
#define COLOR

#include "double_eq.h"
#include <cmath>

struct color {
    float r, g, b;
};

color operator+(color c1, color c2);
color operator-(color c1, color c2);
color operator-(color c);
color operator*(color c, float scalar);

const color BLACK = color{0,0,0};
const color WHITE = color{1,1,1};

// mix colors
color operator*(color c1, color c2);

bool operator==(color c1, color c2);

#endif
