#pragma once

class MLP
{
private:
    std::vector<Layer> layers_;
public:

  Matrix forward(const Matrix& x);
  double train_step(const Matrix& x, const Matrix& target, double learning_rate);
  size_t predict(const Matrix& x);
};

