#include "matrix.hpp"

  Matrix::Matrix(size_t r, size_t c) {
      row_ = r;
      col_ = c;
      data = std::vector<std::vector<double>>(r, std::vector<double>(c, 0.0));
    }

  Matrix::Matrix(const std::vector<std::vector<double>>& m) {
    data = m;
    row_ = m.size();
    if (row_ == 0) {
      col_ = 0;
    } else {
      col_ = m[0].size();
    }
  }

  void Matrix::mat_rand(double minVal, double maxVal) {
    
   static std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<double> dist(minVal, maxVal);

    for (size_t i = 0; i < row_; i++) {
      for (size_t j = 0; j < col_; j++) {
        data[i][j] = dist(gen);
      }
    }
  }

  Matrix Matrix::mat_copy() const {
    Matrix m3(row_, col_);

    for (size_t i = 0; i < row_; i++) {
      for (size_t j = 0; j < col_; j++) {
        (m3.data)[i][j] = data[i][j];
      }
    }
    
    return m3;
  }

  Matrix Matrix::mat_mul(const Matrix& m2) const {
    // Нужно добавить исключения крч
    Matrix m3(row_, m2.col_);

    for (size_t i = 0; i < row_; i++) {
      for (size_t j = 0; j < m2.col_; j++) {
        double sum{0};
        for (size_t k = 0; k < m2.row_; k++) {
          sum += (data[i][k] * (m2.data)[k][j]);
        }
        (m3.data)[i][j] = sum;
      }
    }

    return m3;
  }

  Matrix Matrix::mat_sum(const Matrix& m2) const {
    // Нужно добавить исключения крч
    Matrix m3(row_, col_);

    for (size_t i = 0; i < row_; i++) {
      for (size_t j = 0; j < col_; j++) {
        (m3.data)[i][j] = data[i][j] + (m2.data)[i][j];
      }
    }

    return m3;
  }

  size_t Matrix::row() const {
    return row_;
  }

  size_t Matrix::col() const {
    return col_;
  }

  double Matrix::at(size_t r, size_t c) const {
    return data[r][c];
  }

  double& Matrix::at(size_t r, size_t c) {
    return data[r][c];
  }

  void Matrix::mat_print() const {
    for (size_t i = 0; i < row_; i++) {
      for (size_t j = 0; j < col_; j++) {
        std::cout << std::right << std::setw(print_setw_value) <<  std::fixed << std::setprecision(print_digits_after_dot_count) << data[i][j] << " ";
      }
      std::cout << '\n';
    }
    std::cout << '\n';
  }