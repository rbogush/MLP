#pragma once

enum Activate_func {
  RELU,
  SOFTMAX
};

Matrix Activate_function(const Matrix& m, Activate_func func);
Matrix Relu_act(const Matrix& m);
Matrix Relu_derivative(const Matrix& m);
Matrix Softmax_act(const Matrix& m);