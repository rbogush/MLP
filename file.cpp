#include "file.hpp"

int write_wb_to_file(const Matrix& w1, const Matrix& b1, const Matrix& w2, const Matrix& b2) {
  // Запись w1 и b1
  std::ofstream write("w1b1.txt");
  if (!write) {
    std::cerr << "ОШИБКА ОТКРЫТИЯ ФАЙЛА!\n";
    return 1;
  }
  
  for (size_t i = 0; i < w1.row(); i++) {
    for (size_t j = 0; j < w1.col(); j++) {
      write << std::setprecision(17) << w1.at(i, j);
      if (j < w1.col() - 1) {
        write << " ";
      } else {
        write << "\n";
      }
    }
  }

  for (size_t i = 0; i < b1.row(); i++) {
    for (size_t j = 0; j < b1.col(); j++) {
      write << std::setprecision(17) << b1.at(i, j);
      if (j < b1.col() - 1) {
        write << " ";
      } else {
        write << "\n";
      }
    }
  }

  write.close();

  // Запись w2 и b2

  write.open("w2b2.txt");

  if (!write) {
    std::cerr << "ОШИБКА ОТКРЫТИЯ ФАЙЛА!\n";
    return 1;
  }

  for (size_t i = 0; i < w2.row(); i++) {
    for (size_t j = 0; j < w2.col(); j++) {
      write << std::setprecision(17) << w2.at(i, j);
      if (j < w2.col() - 1) {
        write << " ";
      } else {
        write << "\n";
      }
    }
  }

  for (size_t i = 0; i < b2.row(); i++) {
    for (size_t j = 0; j < b2.col(); j++) {
      write << std::setprecision(17) << b2.at(i, j);
      if (j < b2.col() - 1) {
        write << " ";
      } else {
        write << "\n";
      }
    }
  }

  return 0;
}

int read_wb_from_file(Matrix& w1, Matrix& b1, Matrix& w2, Matrix& b2) {
  // Четние w1 b1

  std::ifstream read("w1b1.txt");

  if (!read) {
    std::cerr << "ОШИБКА ОТКРЫТИЯ ФАЙЛА!\n";
    return 1;
  }

  double num{};
  for (size_t i = 0; i < w1.row(); i++) {
    for (size_t j = 0; j < w1.col(); j++) {
      read >> num;
      w1.at(i, j) = num;
    }
  }

  for (size_t i = 0; i < b1.row(); i++) {
    for (size_t j = 0; j < b1.col(); j++) {
      read >> num;
      b1.at(i, j) = num;
    }
  }

  read.close();

  //Чтение w2 b2

  read.open("w2b2.txt");

  if (!read) {
    std::cerr << "ОШИБКА ОТКРЫТИЯ ФАЙЛА!\n";
    return 1;
  }

  for (size_t i = 0; i < w2.row(); i++) {
    for (size_t j = 0; j < w2.col(); j++) {
      read >> num;
      w2.at(i, j) = num;
    }
  }

  for (size_t i = 0; i < b2.row(); i++) {
    for (size_t j = 0; j < b2.col(); j++) {
      read >> num;
      b2.at(i, j) = num;
    }
  }

  return 0;
}