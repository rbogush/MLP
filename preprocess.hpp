#pragma once

#include <QImage>
#include "matrix.hpp"

// Превращает рисунок в вектор 784x1 в стиле MNIST:
// цифра вписывается в рамку 20x20 с сохранением пропорций и ставится
// в центр картинки 28x28 по центру масс. Значения от 0 до 1.
// Возвращает false, если на рисунке ничего не нарисовано.
bool image_to_mnist(const QImage& source, Matrix& out);