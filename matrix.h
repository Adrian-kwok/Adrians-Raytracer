#ifndef MATRIX
#define MATRIX

#include "tuples.h"
#include <algorithm>

class Matrix {
  float** data; // this could be a smart pointer, but it's more hassle than it's worth
  int x_dim;
  int y_dim;

 public:
  // Big 5
  Matrix(int x_dim, int y_dim);  // gives x by y 0 matrix
  ~Matrix();
  Matrix(const Matrix& m);
  Matrix(Matrix&& m);
  Matrix& operator=(const Matrix& m);
  Matrix& operator=(Matrix&& m);

  int x_size() const;
  int y_size() const;

  void set(int x_ind, int y_ind, float val);   // if outside of indexes does nothing
  float get(int x_ind, int y_ind) const;    // if outside of indexes returns 0
};

bool operator==(const Matrix& m1, const Matrix& m2);
Matrix operator*(const Matrix& m1, const Matrix& m2);

#endif
