#pragma once

class MLP
{
private:
    std::vector<Layer> layers_;
public:

  MLP(const std::vector<Layer>& layers) : layers_(layers) {};

  Matrix forward(const Matrix& x);
  double train_step(const Matrix& x, const Matrix& target, double learning_rate);
  size_t predict(const Matrix& x);
};

