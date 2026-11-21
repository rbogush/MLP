#include "layer.hpp"
#include "matrix.hpp"
#include "activate_func.hpp"

Matrix Layer::forward_pass(const Matrix& m) {

    inputs_ = m;

    Matrix res = weights_.mat_mul(m);
    res = res.mat_sum(biases_);

    z_before_act_ = res;

    res = Activate_function(res, act_func_);

    return res;
  }

Matrix Layer::back_propogation(const Matrix& grad) {
    Matrix dz = grad;

    if (act_func_ == RELU) {
      dz = dz.mat_mul_adamar(Relu_derivative(z_before_act_));
    }

    db_ = dz;
    dW_ = dz.mat_mul(inputs_.mat_trans());

    return weights_.mat_trans().mat_mul(dz);
  }

void Layer::update(double learning_rate) {
  
  weights_ = weights_.mat_sub(dW_.mat_scale(learning_rate));
  biases_ = biases_.mat_sub(db_.mat_scale(learning_rate));
}