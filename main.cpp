#include "network.hpp"

int main() {

  Matrix m1(3, 3);
  Matrix m2(3, 3);
  m1.mat_rand(-10, 10);
  m2.mat_rand(-10, 10);
  Matrix m3(3, 3);
  m1.mat_print();
  m2.mat_print();
  m3 = m1.mat_sum(m2);
  m3.mat_print();
  m3 = m1.mat_mul(m2);
  m3.mat_print();
  return 0;
}