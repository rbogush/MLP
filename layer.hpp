#pragma once

#include <vector>
#include "matrix.hpp"
#include "activate_func.hpp"

class Layer
{
private:

  Matrix inputs_;
  Matrix z_before_act_;
  Matrix weights_;
  Matrix biases_;
  Matrix dW_;
  Matrix db_;
  Activate_func act_func_;

public:

  Layer(const Matrix& w, const Matrix& b, Activate_func act_f) : weights_(w), biases_(b), act_func_(act_f) {};
  Matrix forward_pass(const Matrix& m);
  Matrix back_propogation(const Matrix& grad);
  
};

