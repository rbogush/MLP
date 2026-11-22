#pragma once

#include <vector>
#include "matrix.hpp"
#include "activate_func.hpp"

class Layer
{
private:

  Matrix weights_;
  Matrix biases_;
  Activate_func act_func_;
  Matrix dW_;
  Matrix db_;
  Matrix inputs_;
  Matrix z_before_act_;

public:

  Layer(const Matrix& w, const Matrix& b, Activate_func act_f) : weights_(w), biases_(b), act_func_(act_f) {};
  Matrix forward_pass(const Matrix& m);
  Matrix back_propogation(const Matrix& grad);
  void update(double learning_rate);
  Matrix get_w() const;
  Matrix get_b() const;
  void set_w(const Matrix& m);
  void set_b(const Matrix& m);
};

