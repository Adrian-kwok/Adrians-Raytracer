#include "double_eq.h"

bool equal(double f1, double f2) {
    return abs(f1 - f2) < EPSILON;
}

bool equal(float f1, float f2) {
    return abs(f1 - f2) < EPSILON;
}

double absolute(double d) {
    if (d < 0) {
        return -d;
    } else {
        return d;
    }
}
