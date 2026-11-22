#include "preprocess.hpp"

#include <cmath>

bool image_to_mnist(const QImage& source, Matrix& out) {
  const int kBox = 20;      // в такую рамку вписывается цифра
  const int kSide = 28;     // размер итоговой картинки
  const int kThreshold = 20; // пиксель темнее этого считаем фоном

  QImage gray = source.convertToFormat(QImage::Format_Grayscale8);

  // 1. Границы нарисованного
  int min_x = gray.width();
  int min_y = gray.height();
  int max_x = -1;
  int max_y = -1;

  for (int y = 0; y < gray.height(); y++) {
    const uchar* line = gray.constScanLine(y);
    for (int x = 0; x < gray.width(); x++) {
      if (line[x] > kThreshold) {
        if (x < min_x) {
          min_x = x;
        }
        if (x > max_x) {
          max_x = x;
        }
        if (y < min_y) {
          min_y = y;
        }
        if (y > max_y) {
          max_y = y;
        }
      }
    }
  }

  if (max_x < 0) {
    return false;
  }

  // 2. Вырезаем и сжимаем так, чтобы большая сторона стала 20 пикселей
  QImage cropped = gray.copy(min_x, min_y, max_x - min_x + 1, max_y - min_y + 1);
  QImage small = cropped.scaled(kBox, kBox, Qt::KeepAspectRatio, Qt::SmoothTransformation);

  // 3. Центр масс
  double sum = 0.0;
  double sum_x = 0.0;
  double sum_y = 0.0;

  for (int y = 0; y < small.height(); y++) {
    const uchar* line = small.constScanLine(y);
    for (int x = 0; x < small.width(); x++) {
      double value = line[x];
      sum += value;
      sum_x += value * x;
      sum_y += value * y;
    }
  }

  if (sum <= 0.0) {
    return false;
  }

  double center_x = sum_x / sum;
  double center_y = sum_y / sum;

  // сдвиг, при котором центр масс попадёт в центр 28x28
  int shift_x = static_cast<int>(std::lround(kSide / 2.0 - center_x));
  int shift_y = static_cast<int>(std::lround(kSide / 2.0 - center_y));

  // 4. Раскладываем по 784 числам (строка за строкой, как в MNIST)
  for (size_t i = 0; i < out.row(); i++) {
    out.at(i, 0) = 0.0;
  }

  for (int y = 0; y < small.height(); y++) {
    const uchar* line = small.constScanLine(y);
    for (int x = 0; x < small.width(); x++) {
      int target_x = x + shift_x;
      int target_y = y + shift_y;
      if (target_x >= 0 && target_x < kSide && target_y >= 0 && target_y < kSide) {
        out.at(static_cast<size_t>(target_y * kSide + target_x), 0) = line[x] / 255.0;
      }
    }
  }

  return true;
}