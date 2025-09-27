#include "double_eq.h"

const double EPSILON = 0.00001;

bool equal(double f1, double f2) {
    return abs(f1 - f2) < EPSILON;
}

bool equal(float f1, float f2) {
    return abs(f1 - f2) < EPSILON;
}
