#include "tuples.h"

tuple operator+(tuple t1, tuple t2) {
  return tuple{t1.x + t2.x, t1.y + t2.y, t1.z + t2.z, t1.type + t2.type};
}
tuple operator-(tuple t1, tuple t2) {
  return tuple{t1.x - t2.x, t1.y - t2.y, t1.z - t2.z, t1.type - t2.type};
}
tuple operator-(tuple t) { return tuple{-t.x, -t.y, -t.z, t.type}; }
tuple operator*(tuple t, float scalar) {
  return tuple{t.x * scalar, t.y * scalar, t.z * scalar, t.type};
}
// scalar cannot be 0, else 0 vector is returned
tuple operator/(tuple t, float scalar) {
  if (scalar == 0) {
    return ZEROVEC;
  } else {
    return tuple{t.x / scalar, t.y / scalar, t.z / scalar, t.type};
  }
}

bool operator==(tuple t1, tuple t2) {
  return (equal(t1.x, t2.x) && equal(t1.y, t2.y) && equal(t1.z, t2.z));
}

float norm(tuple t) { return sqrt(t.x * t.x + t.y * t.y + t.z * t.z); }

tuple normalize(tuple t) { return t / norm(t); }

float dot(tuple t1, tuple t2) {
  return t1.x * t2.x + t1.y * t2.y + t1.z * t2.z;
}

tuple cross(tuple t1, tuple t2) {
  return tuple{(t1.y * t2.z) - (t1.z * t2.y), 
               (t1.z * t2.x) - (t1.x * t2.z),
               (t1.x * t2.y) - (t1.y * t1.x), 
               0};
}
