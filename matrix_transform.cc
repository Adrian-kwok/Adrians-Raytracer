#include "matrix_transform.h"

Matrix translate(const tuple& t) {
  Matrix mat = identity(TUPLE_SIZE);

  // creating translation matrix
  for (int i = 0; i < TUPLE_SIZE - 1; i++) {
    mat.set(i, TUPLE_SIZE - 1, t.get(i));
  }
  return mat;
}

Matrix translate(double x, double y, double z) {
  return translate(vector(x, y, z));
}

Matrix scale(const tuple& t) {
  Matrix mat = identity(TUPLE_SIZE);

  // creating scaling matrix
  for (int i = 0; i < TUPLE_SIZE - 1; i++) {
    mat.set(i, i, t.get(i));
  }
  return mat;
}

Matrix scale(double x, double y, double z) { return scale(vector(x, y, z)); }

Matrix roto_x(double rads) {
  Matrix mat = identity(TUPLE_SIZE);

  mat.set(1, 1, cos(rads));
  mat.set(1, 2, -sin(rads));
  mat.set(2, 1, sin(rads));
  mat.set(2, 2, cos(rads));

  return mat;
}

Matrix roto_y(double rads) {
  Matrix mat = identity(TUPLE_SIZE);

  mat.set(0, 0, cos(rads));
  mat.set(2, 0, -sin(rads));
  mat.set(0, 2, sin(rads));
  mat.set(2, 2, cos(rads));

  return mat;
}

Matrix roto_z(double rads) {
  Matrix mat = identity(TUPLE_SIZE);

  mat.set(0, 0, cos(rads));
  mat.set(0, 1, -sin(rads));
  mat.set(1, 0, sin(rads));
  mat.set(1, 1, cos(rads));

  return mat;
}

Matrix shear(double xpy, double xpz, double ypx, double ypz, double zpx,
             double zpy) {
  Matrix mat = identity(TUPLE_SIZE);

  mat.set(0, 1, xpy);
  mat.set(0, 2, xpz);
  mat.set(1, 0, ypx);
  mat.set(1, 2, ypz);
  mat.set(2, 0, zpx);
  mat.set(2, 1, zpy);

  return mat;
}
