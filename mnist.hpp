#pragma once
#include <string>
#include <vector>
#include "matrix.hpp"

std::vector<std::vector<unsigned char>> load_images(const std::string& path);
std::vector<int> load_labels(const std::string& path);
Matrix to_matrix(const std::vector<unsigned char>& img);  // 784x1, значения от 0 до 1
Matrix make_target(int label);                             // 10x1, one-hot