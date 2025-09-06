#include "float_eq.h"

const float EPSILON = 0.00001;

bool equal(float f1, float f2) {
    return abs(f1 - f2) < EPSILON;
}
