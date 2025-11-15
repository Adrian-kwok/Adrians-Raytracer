#include "matrix.h"

Matrix::Matrix(int row_dim, int col_dim)
    : data{nullptr}, row_dim{row_dim}, col_dim{col_dim} {
  data = new double*[row_dim];
  for (int i = 0; i < row_dim; i++) {
    data[i] = new double[col_dim];
    for (int j = 0; j < col_dim; j++) {
      data[i][j] = 0;
    }
  }
}

Matrix::Matrix(int row_dim, int col_dim, std::string input)
    : data{nullptr}, row_dim{row_dim}, col_dim{col_dim} {
  data = new double*[row_dim];
  std::istringstream iss{input};

  for (int i = 0; i < row_dim; i++) {
    data[i] = new double[col_dim];
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
  data = new double*[row_dim];
  for (int i = 0; i < row_dim; i++) {
    data[i] = new double[col_dim];
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
  if (&m == this) return *this;

  Matrix temp {m};
  std::swap(data, temp.data);
  std::swap(row_dim, temp.row_dim);
  std::swap(col_dim, temp.col_dim);

  return *this;
}

Matrix& Matrix::operator=(Matrix&& m) {
  if (&m == this) return *this;

  std::swap(data, m.data);
  std::swap(row_dim, m.row_dim);
  std::swap(col_dim, m.col_dim);

  return *this;
}

int Matrix::num_rows() const { return row_dim; }
int Matrix::num_cols() const { return col_dim; }

void Matrix::set(int row_ind, int col_ind, double val) {
  if (!(row_ind >= row_dim || row_ind < 0 || col_ind >= col_dim ||
        col_ind < 0)) {  // do nothing if out of bounds
    data[row_ind][col_ind] = val;
  }
}

double Matrix::get(int row_ind, int col_ind) const {
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
        if (!equal(m1.get(i, j), m2.get(i, j))) {
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
      double temp = 0;
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
    double temp = 0;
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

double cofactor(const Matrix& m, int row, int col) {
  Matrix submat{submatrix(m, row, col)};
  if ((row + col) % 2 == 0) {
    return det(submat);
  } else {
    return -det(submat);
  }
}

double det(const Matrix& m) {
  if (m.num_rows() != m.num_cols()) {  // check for non-square matricies
    return 0;
  }
  if (m.num_rows() == 1) {  // 1d matrix, trivial
    return m.get(0, 0);

    // will probably pay divedens to write out the 2d case
  } else if (m.num_rows() == 2) {
    return m.get(0, 0) * m.get(1, 1) - m.get(1, 0) * m.get(0, 1);
  } else {
    // performing gaussian elimination
    Matrix temp_mat{m};

    bool swap = false;

    // first finding a non-zero element in the first spot of the matrix
    if (temp_mat.get(0, 0) == 0) {
      for (int i = 0; i < temp_mat.num_rows(); i++) {
        if (temp_mat.get(i, 0) != 0) {
          swap = true;

          // swapping to get non-zero value at 0,0
          for (int j = 0; j < temp_mat.num_cols(); j++) { 
            double temp = temp_mat.get(0, j);
            temp_mat.set(0, j, temp_mat.get(i, j));
            temp_mat.set(i, j, temp);
          }
        }
      }

      if (!swap) {  // in this case the entire first col is 0 => det is 0
        return 0;
      }
    }

    // now can assume number at 0,0 is non-zero
    for (int i = 1; i < temp_mat.num_rows(); i++) {
      if (temp_mat.get(i, 0) == 0) {  // trivial case for gausian elimination
        continue;
      }

      double factor = temp_mat.get(i, 0) / temp_mat.get(0, 0);
      for (int j = 0; j < temp_mat.num_cols(); j++) {
        temp_mat.set(i, j, temp_mat.get(i, j) - temp_mat.get(0, j) * factor);
      }
    }

    if (swap) {
      return -(temp_mat.get(0,0) * det(submatrix(temp_mat, 0, 0)));
    } else {
      return (temp_mat.get(0,0) * det(submatrix(temp_mat, 0, 0)));
    }
  }
}

Matrix transpose(const Matrix& m) {
  Matrix t {m.num_cols(), m.num_rows()};

  for (int i = 0; i < m.num_cols(); i++) {
    for (int j = 0; j < m.num_rows(); j++) {
      t.set(i, j, m.get(j, i));
    }
  }
  
  return t;
}

// this function is dumb
bool is_invertible(const Matrix& m) {
  return (det(m) != 0);
}

Matrix inverse(const Matrix& m) {
  double determinant = det(m);
  if (determinant == 0) {
    std::cerr << "Error: trying to invert non-invertible matrix" << std::endl;
    return DEFAULT;
  }
  
  Matrix inv {m.num_rows(), m.num_cols()};

  for (int i = 0; i < inv.num_rows(); i++) {
    for (int j = 0; j < inv.num_cols(); j++) {
      inv.set(i,j, cofactor(m,i,j) / determinant);
    }
  }

  return transpose(inv);
}

bool Matrix::operator==(const Matrix& other) {
  if (other.col_dim == col_dim && other.row_dim == row_dim) {
    for (int i = 0; i < col_dim; i++) {
      for (int j = 0; j < row_dim; j++) {
        if (get(i,j) != other.get(i,j)) {
          return false;
        }
      }
    }
    return true;
  } else {
    return false;
  }
}
