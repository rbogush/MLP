#pragma once

#include <vector>
#include "matrix.hpp"
#include "activate_func.hpp"

class Layer
{
private:

  Matrix weights_;
  Matrix biases_;
  Activate_func act_func;

public:

  Layer(const Matrix& w, const Matrix& b, Activate_func act_f) : weights_(w), biases_(b), act_func(act_f) {};
  Matrix forward_pass(const Matrix& m) const;
  
};

