#include "layer.hpp"
#include "matrix.hpp"
#include "activate_func.hpp"

Matrix Layer::forward_pass(const Matrix& m) const {

    Matrix res = m.mat_mul(weights_);
    res = res.mat_sum(biases_);

    res = Activate_function(res, act_func);

    return res;
  }