#include "tuples.h"

tuple point(float x, float y, float z) { return tuple{x, y, z, 1}; }

tuple vector(float x, float y, float z) { return tuple{x, y, z, 0}; }

void tuple::set(int ind, float val) {
  if (ind == 0) {
    x = val;
  } else if (ind == 1) {
    y = val;
  } else if (ind == 2) {
    z = val;
  } else if (ind == 3) {
    w = val;
  }
}

float tuple::get(int ind) const{
  if (ind == 0) {
    return x;
  } else if (ind == 1) {
    return y;
  } else if (ind == 2) {
    return z;
  } else if (ind == 3) {
    return w;
  } else {
    return 0;
  }
}

tuple operator+(tuple t1, tuple t2) {
  return tuple{t1.x + t2.x, t1.y + t2.y, t1.z + t2.z, t1.w + t2.w};
}
tuple operator-(tuple t1, tuple t2) {
  return tuple{t1.x - t2.x, t1.y - t2.y, t1.z - t2.z, t1.w - t2.w};
}
tuple operator-(tuple t) { return tuple{-t.x, -t.y, -t.z, -t.w}; }

tuple operator*(tuple t, float scalar) {
  return tuple{t.x * scalar, t.y * scalar, t.z * scalar, t.w * scalar};
}

// scalar cannot be 0, else 0 vector is returned
tuple operator/(tuple t, float scalar) {
  if (scalar == 0) {
    return ZEROVEC;
  } else {
    return tuple{t.x / scalar, t.y / scalar, t.z / scalar, t.w / scalar};
  }
}

bool operator==(tuple t1, tuple t2) {
  return (equal(t1.x, t2.x) && equal(t1.y, t2.y) && equal(t1.z, t2.z) &&
          equal(t1.w, t2.w));
}

float norm(tuple t) {
  return sqrt(t.x * t.x + t.y * t.y + t.z * t.z + t.w * t.w);
}

tuple normalize(tuple t) { return t / norm(t); }

float dot(tuple t1, tuple t2) {
  return t1.x * t2.x + t1.y * t2.y + t1.z * t2.z + t1.w * t2.w;
}

tuple cross(tuple t1, tuple t2) {
  return vector((t1.y * t2.z) - (t1.z * t2.y), (t1.z * t2.x) - (t1.x * t2.z),
                (t1.x * t2.y) - (t1.y * t1.x));
}
