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

// mix colors
color operator*(color c1, color c2);

bool operator==(color c1, color c2);

#endif
