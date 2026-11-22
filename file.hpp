#pragma once

#include <fstream>
#include "matrix.hpp"

int write_wb_to_file(const Matrix& w1, const Matrix& b1, const Matrix& w2, const Matrix& b2);
int read_wb_from_file(Matrix& w1, Matrix& b1, Matrix& w2, Matrix& b2);

