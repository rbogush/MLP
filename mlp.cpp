#include "layer.hpp"
#include "matrix.hpp"
#include "activate_func.hpp"
#include "mlp.hpp"

Matrix MLP::forward(const Matrix& x) {
    Matrix a = x;

    for (size_t i = 0; i < layers_.size(); i++) {
      a = layers_[i].forward_pass(a);
    }

    return a;
  }

  double MLP::train_step(const Matrix& x, const Matrix& target, double learning_rate) {
    //Шаг 1 - Вперед
    Matrix pred = forward(x);

    //Шаг 2 Вывод ошибки

    double loss{0};
    for (size_t i = 0; i < target.row(); i++) {
      if (target.at(i, 0) == 1) {
        loss = -std::log(pred.at(i, 0)); 
      }
    }

    //Шаг 3 - Назад
    Matrix grad = pred.mat_sub(target);
    for (size_t i = layers_.size() - 1; i >= 0 ; i--) {
      grad = layers_[i].back_propogation(grad);
    }

    //Шаг 4 - обновление

    for (size_t i = 0; i < layers_.size(); i++) {
      layers_[i].update(learning_rate);
    }

    return loss;
  }

  size_t MLP::predict(const Matrix& x) {
    Matrix pred = forward(x);
    size_t max = 0;

    for (size_t i = 1; i < x.row(); i++) {
      if (pred.at(i, 0) > pred.at(max, 0)) {
        max = i;
      }
    }

    return max;
  }