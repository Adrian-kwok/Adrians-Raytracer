#include "matrix.h"

Matrix::Matrix(int row_dim, int col_dim)
    : data{nullptr}, row_dim{row_dim}, col_dim{col_dim} {
  data = new float*[row_dim];
  for (int i = 0; i < row_dim; i++) {
    data[i] = new float[col_dim];
    for (int j = 0; j < col_dim; j++) {
      data[i][j] = 0;
    }
  }
}

Matrix::Matrix(int row_dim, int col_dim, std::string input)
    : data{nullptr}, row_dim{row_dim}, col_dim{col_dim} {
  data = new float*[row_dim];
  std::istringstream iss {input};

  for (int i = 0; i < row_dim; i++) {
    data[i] = new float[col_dim];
    for (int j = 0; j < col_dim; j++) {
      if (!(iss >> data[i][j])) {
        data[i][j] = 0;
      }
    }
  }
}

Matrix::~Matrix() {
  if (data != nullptr) {
    for (int i = 0; i < row_dim; i++) {
      delete[] data[i];
    }
    delete[] data;
  }
}

Matrix::Matrix(const Matrix& m)
    : data{nullptr}, row_dim{m.row_dim}, col_dim{m.col_dim} {
  data = new float*[row_dim];
  for (int i = 0; i < row_dim; i++) {
    data[i] = new float[col_dim];
    for (int j = 0; j < col_dim; j++) {
      data[i][j] = m.data[i][j];
    }
  }
}

Matrix::Matrix(Matrix&& m)
    : data{m.data}, row_dim{m.row_dim}, col_dim{m.col_dim} {
  m.data = nullptr;
}

Matrix& Matrix::operator=(const Matrix& m) {
  if (data != nullptr) {
    for (int i = 0; i < row_dim; i++) {
      delete[] data[i];
    }
    delete[] data;
  }

  row_dim = m.row_dim;
  col_dim = m.col_dim;

  data = new float*[row_dim];
  for (int i = 0; i < row_dim; i++) {
    data[i] = new float[col_dim];
    for (int j = 0; j < col_dim; j++) {
      data[i][j] = m.data[i][j];
    }
  }

  return *this;
}

Matrix& Matrix::operator=(Matrix&& m) {
  std::swap(data, m.data);
  std::swap(row_dim, m.row_dim);
  std::swap(col_dim, m.col_dim);

  return *this;
}

int Matrix::num_rows() const { return row_dim; }
int Matrix::num_cols() const { return col_dim; }

void Matrix::set(int row_ind, int col_ind, float val) {
  if (!(row_ind >= row_dim || row_ind < 0 || col_ind >= col_dim ||
        col_ind < 0)) {  // do nothing if out of bounds
    data[row_ind][col_ind] = val;
  }
}

float Matrix::get(int row_ind, int col_ind) const {
  if (row_ind >= row_dim || row_ind < 0 || col_ind >= col_dim ||
      col_ind < 0) {  // if out of bounds return 0
    return 0;
  } else {
    return data[row_ind][col_ind];
  }
}

bool operator==(const Matrix& m1, const Matrix& m2) {
  if (m1.num_rows() == m2.num_rows() && m1.num_cols() == m2.num_cols()) {
    for (int i = 0; i < m1.num_rows(); i++) {
      for (int j = 0; j < m1.num_cols(); j++) {
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

Matrix operator*(const Matrix& m1, const Matrix& m2) {
  Matrix mat{m1.num_rows(), m2.num_cols()};
  if (m1.num_cols() != m2.num_rows()) {
    return DEFAULT;
  }

  for (int i = 0; i < mat.num_rows(); i++) {
    for (int j = 0; j < mat.num_cols(); j++) {
      float temp = 0;
      for (int k = 0; k < m1.num_cols(); k++) {
        temp += m1.get(i, k) * m2.get(k, j);
      }
      mat.set(i, j, temp);
    }
  }

  return mat;
}

tuple operator*(const Matrix& m, const tuple& t) {
  tuple result = ZEROVEC;

  // because of the way get works, 0 is returned if index is OOB, as desired
  for (int i = 0; i < TUPLE_SIZE; i++) {
    float temp = 0;
    for (int j = 0; j < TUPLE_SIZE; j++) {
      temp += m.get(i, j) * t.get(j);
    }
    result.set(i, temp);
  }
  // maybe using the get and set commands, while clean, is too performance
  // intensive? test this later

  return result;
}

Matrix identity(int dim) {
  Matrix mat{dim, dim};
  for (int i = 0; i < dim; i++) {
    mat.set(i, i, 1);
  }
  return mat;
}

Matrix submatrix(const Matrix& m, int row, int col) {
  if (m.num_cols() != m.num_rows()) {
    return DEFAULT;
  }

  Matrix mat{m.num_cols() - 1, m.num_rows() - 1};

  for (int i = 0; i < m.num_rows(); i++) {
    if (i == row) {
      continue;
    }

    for (int j = 0; j < m.num_cols(); j++) {
      if (j == col) {
        continue;  // skipping the col
      }
      mat.set(i > row ? i - 1 : i, j > col ? j - 1 : j, m.get(i, j));
    }
  }

  return mat;
}

float cofactor(const Matrix& m, int row, int col) {
  Matrix submat{submatrix(m, row, col)};
  if ((row + col) % 2 == 0) {
    return det(submat);
  } else {
    return -det(submat);
  }
}

float det(const Matrix& m) {
  if (m.num_rows() != m.num_cols()) {  // check for non-square matricies
    return 0;
  }
  if (m.num_rows() == 1) {  // 1d matrix, trivial
    return m.get(0, 0);

    // will probably pay divedens to write out the 2d case
  } else if (m.num_rows() == 2) {
    return m.get(0, 0) * m.get(1, 1) - m.get(1, 0) * m.get(0, 1);
  } else {
    float result = 0;
    for (int i = 0; i < m.num_cols(); i++) {
      result += m.get(0, i) * cofactor(m, 0, i);
    }
    return result;
  }
}
