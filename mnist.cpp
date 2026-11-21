#include "mnist.hpp"
#include <fstream>
#include <stdexcept>

static int read_int(std::ifstream& f) {
  unsigned char b[4];
  f.read(reinterpret_cast<char*>(b), 4);
  return (b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3];
}

std::vector<std::vector<unsigned char>> load_images(const std::string& path) {
  std::ifstream f(path, std::ios::binary);
  if (!f) {
    throw std::runtime_error("cannot open " + path);
  }

  int magic = read_int(f);
  int count = read_int(f);
  int rows = read_int(f);
  int cols = read_int(f);
  if (magic != 2051) {
    throw std::runtime_error("bad images file: " + path);
  }

  std::vector<std::vector<unsigned char>> images(count, std::vector<unsigned char>(rows * cols));
  for (int n = 0; n < count; n++) {
    f.read(reinterpret_cast<char*>(images[n].data()), rows * cols);
  }
  return images;
}

std::vector<int> load_labels(const std::string& path) {
  std::ifstream f(path, std::ios::binary);
  if (!f) {
    throw std::runtime_error("cannot open " + path);
  }

  int magic = read_int(f);
  int count = read_int(f);
  if (magic != 2049) {
    throw std::runtime_error("bad labels file: " + path);
  }

  std::vector<int> labels(count);
  for (int n = 0; n < count; n++) {
    unsigned char label;
    f.read(reinterpret_cast<char*>(&label), 1);
    labels[n] = label;
  }
  return labels;
}

Matrix to_matrix(const std::vector<unsigned char>& img) {
  Matrix m(img.size(), 1);
  for (size_t i = 0; i < img.size(); i++) {
    m.at(i, 0) = img[i] / 255.0;   // без этого деления сеть сломается
  }
  return m;
}

Matrix make_target(int label) {
  Matrix t(10, 1);
  t.at(label, 0) = 1.0;
  return t;
}