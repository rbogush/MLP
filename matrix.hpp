#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <random>

// Constants

const int print_setw_value = 8;
const int print_digits_after_dot_count = 2;

// Matrix class

class Matrix
{
private:
  size_t row_, col_;
  std::vector<std::vector<double>> data;

public:

  Matrix(size_t r, size_t c);
  Matrix(const std::vector<std::vector<double>>& m);
  void mat_rand(double minVal, double maxVal);
  Matrix mat_copy() const;
  Matrix mat_mul(const Matrix& m2) const;
  Matrix mat_sum(const Matrix& m2) const;
  size_t row() const;
  size_t col() const;
  double at(size_t r, size_t c) const;
  double& at(size_t r, size_t c);
  void mat_print() const;

};

