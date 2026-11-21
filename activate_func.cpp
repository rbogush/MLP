#include "matrix.hpp"
#include "activate_func.hpp"

Matrix Activate_function(const Matrix& m, Activate_func func) {
  switch (func) {
    case RELU:
      return Relu_act(m);
    case SOFTMAX:
      return Softmax_act(m);
  }

  return m;
  // Добавить исключения
}

Matrix Relu_act(const Matrix& m) {

  Matrix res(m.row(), m.col());

  for (size_t i = 0; i < m.row(); i++) {
    for (size_t j = 0; j < m.col(); j++) {
      if (m.at(i, j) <= 0) {
        res.at(i, j) = 0;
      } else {
        res.at(i, j) = m.at(i, j);
      }
    }
  }

  return res;
}

Matrix Relu_derivative(const Matrix& m) {

  Matrix res(m.row(), m.col());

  for (size_t i = 0; i < m.row(); i++) {
    for (size_t j = 0; j < m.col(); j++) {
      if (m.at(i, j) <= 0) {
        res.at(i, j) = 0;
      } else {
        res.at(i, j) = 1;
      }
    }
  }

  return res;
}

Matrix Softmax_act(const Matrix& m) {

  Matrix res(m.row(), m.col());

  for (size_t i = 0; i < m.col(); i++) {

    double max_element{m.at(0, i)};

    for (size_t j = 1; j < m.row(); j++) {
      if (m.at(j, i) > max_element) {
        max_element = m.at(j, i);
      }
    }

    double sum{0};
    for (size_t j = 0; j < m.row(); j++) {
      res.at(j, i) = std::exp(m.at(j, i) - max_element);
      sum += res.at(j, i);
      
    }

    for (size_t j = 0; j < m.row(); j++) {
      res.at(j, i) /= sum;
    }
  }

  return res;
}