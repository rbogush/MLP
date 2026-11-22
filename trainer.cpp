#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include "matrix.hpp"
#include "activate_func.hpp"
#include "layer.hpp"
#include "mlp.hpp"
#include "mnist.hpp"

void print_digit(const std::vector<unsigned char>& img) {
  for (size_t r = 0; r < 28; r++) {
    for (size_t c = 0; c < 28; c++) {
      if (img[r * 28 + c] > 127) {
        std::cout << "#";
      } else {
        std::cout << ".";
      }
    }
    std::cout << "\n";
  }
}

double accuracy(MLP& net,
                const std::vector<std::vector<unsigned char>>& xs,
                const std::vector<int>& ys) {
  size_t correct = 0;
  for (size_t k = 0; k < xs.size(); k++) {
    if (net.predict(to_matrix(xs[k])) == static_cast<size_t>(ys[k])) {
      correct++;
    }
  }
  return 100.0 * correct / xs.size();
}

int main() {
  try {
    auto train_x = load_images("train-images.idx3-ubyte");
    auto train_y = load_labels("train-labels.idx1-ubyte");
    auto test_x = load_images("t10k-images.idx3-ubyte");
    auto test_y = load_labels("t10k-labels.idx1-ubyte");

    // ПРОВЕРКА ЗАГРУЗКИ: 60000 60000 10000 10000, первая метка 5
    std::cout << train_x.size() << " " << train_y.size() << " "
              << test_x.size() << " " << test_y.size() << std::endl;
    std::cout << "first label: " << train_y[0] << std::endl;
    print_digit(train_x[0]);   // тут должна быть видна пятёрка

    // сеть 784 -> 128 (ReLU) -> 10 (Softmax)
    double limit1 = std::sqrt(6.0 / (784 + 128));
    Matrix w1(128, 784);
    w1.mat_rand(-limit1, limit1);
    Matrix b1(128, 1);

    double limit2 = std::sqrt(6.0 / (128 + 10));
    Matrix w2(10, 128);
    w2.mat_rand(-limit2, limit2);
    Matrix b2(10, 1);

    std::vector<Layer> layers{{w1, b1, RELU}, {w2, b2, SOFTMAX}};
    MLP net(layers);

    // индексы для перемешивания порядка картинок
    std::vector<size_t> order(train_x.size());
    std::iota(order.begin(), order.end(), 0);
    std::mt19937 gen(std::random_device{}());

    const int EPOCHS = 5;
    for (int epoch = 0; epoch < EPOCHS; epoch++) {
      std::shuffle(order.begin(), order.end(), gen);

      double total_loss = 0;
      for (size_t k = 0; k < order.size(); k++) {
        size_t idx = order[k];
        total_loss += net.train_step(to_matrix(train_x[idx]),
                                     make_target(train_y[idx]),
                                     LEARNING_RATE);
      }

      std::cout << "epoch " << epoch
                << ": loss = " << total_loss / order.size()
                << ", test accuracy = " << accuracy(net, test_x, test_y) << "%"
                << std::endl;
    }


    // проверка на настоящей двойке из тестового набора
    for (size_t k = 0; k < test_x.size(); k++) {
      if (test_y[k] == 2) {
        print_digit(test_x[k]);
        std::cout << "predict: " << net.predict(to_matrix(test_x[k])) << std::endl;
        break;
      }
    }

    if (net.w_layers() != 0) {
      return 1;
    }
  } catch (const std::exception& e) {
    std::cout << "ERROR: " << e.what() << std::endl;
    return 1;
  }

  
  return 0;
}