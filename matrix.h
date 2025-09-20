#ifndef MATRIX
#define MATRIX

#include "tuples.h"
#include <algorithm>
#include <iostream>
#include <sstream>

const int TUPLE_SIZE = 4;

class Matrix {
  float** data; // this could be a smart pointer, but it's more hassle than it's worth
  int row_dim;
  int col_dim;

 public:
  // Big 5
  Matrix(int row_dim, int col_dim);  // gives x by y 0 matrix, if values are invalid returns default matrix
  Matrix(int row_dim, int col_dim, std::string input); // entries in string are seperated with single spaces
  ~Matrix();
  Matrix(const Matrix& m);
  Matrix(Matrix&& m);
  Matrix& operator=(const Matrix& m);
  Matrix& operator=(Matrix&& m);

  int num_rows() const;
  int num_cols() const;

  void set(int row_ind, int col_ind, float val);   // if outside of indexes does nothing
  float get(int row_ind, int col_ind) const;    // if outside of indexes returns 0
};

Matrix identity(int dim);

bool operator==(const Matrix& m1, const Matrix& m2);
Matrix operator*(const Matrix& m1, const Matrix& m2); // returns default matrix if not possible
tuple operator*(const Matrix& m, const tuple& t); // only works with 4x4 matrix otherwise returns ZEROVEC

// submatrix also assumes a square matrix
Matrix submatrix(const Matrix& m, int row, int col); //  row and col better not be OOB!
float cofactor(const Matrix& m, int row, int col);
float det(const Matrix& m);

const Matrix DEFAULT {1,1};
const Matrix IDENTITY = identity(TUPLE_SIZE);

#endif
