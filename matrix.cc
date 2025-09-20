#include "matrix.h"

Matrix::Matrix(int x_dim, int y_dim)
    : data{nullptr}, x_dim{x_dim}, y_dim{y_dim} {
  data = new float*[x_dim];
  for (int i = 0; i < x_dim; i++) {
    data[i] = new float[y_dim];
    for (int j = 0; j < y_dim; j++) {
      data[i][j] = 0;
    }
  }
}

Matrix::~Matrix() {
  if (data != nullptr) {
    for (int i = 0; i < x_dim; i++) {
      delete[] data[i];
    }
    delete[] data;
  }
}

Matrix::Matrix(const Matrix& m)
    : data{nullptr}, x_dim{m.x_dim}, y_dim{m.y_dim} {
  data = new float*[x_dim];
  for (int i = 0; i < x_dim; i++) {
    data[i] = new float[y_dim];
    for (int j = 0; j < y_dim; j++) {
      data[i][j] = m.data[i][j];
    }
  }
}

Matrix::Matrix(Matrix&& m) : data{m.data}, x_dim{m.x_dim}, y_dim{m.y_dim} {
  m.data = nullptr;
}

Matrix& Matrix::operator=(const Matrix& m) {
  if (data != nullptr) {
    for (int i = 0; i < x_dim; i++) {
      delete[] data[i];
    }
    delete[] data;
  }

  x_dim = m.x_dim;
  y_dim = m.y_dim;

  data = new float*[x_dim];
  for (int i = 0; i < x_dim; i++) {
    data[i] = new float[y_dim];
    for (int j = 0; j < y_dim; j++) {
      data[i][j] = m.data[i][j];
    }
  }

  return *this;
}

Matrix& Matrix::operator=(Matrix&& m) {
  std::swap(data, m.data);
  std::swap(x_dim, m.x_dim);
  std::swap(y_dim, m.y_dim);

  return *this;
}

int Matrix::x_size() const { return x_dim; }
int Matrix::y_size() const { return y_dim; }

void Matrix::set(int x_ind, int y_ind, float val) {
  if (!(x_ind >= x_dim || x_ind < 0 || y_ind >= y_dim ||
        y_ind < 0)) {  // do nothing if out of bounds
    data[x_ind][y_ind] = val;
  }
}

float Matrix::get(int x_ind, int y_ind) const {
  if (x_ind >= x_dim || x_ind < 0 || y_ind >= y_dim ||
      y_ind < 0) {  // if out of bounds return 0
    return 0;
  } else {
    return data[x_ind][y_ind];
  }
}

bool operator==(const Matrix& m1, const Matrix& m2) {
  if (m1.x_size() == m2.x_size() && m1.y_size() == m2.y_size()) {
    for (int i = 0; i < m1.x_size(); i++) {
      for (int j = 0; j < m1.y_size(); j++) {
        if (m1.get(i, j) != m2.get(i, j)) {
          return false;  // if one doesn't match return false
        }
      }
    }
    // if all match return true
    return true;

  } else {
    return false;
  }
}
