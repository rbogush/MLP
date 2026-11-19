#include "matrix.hpp"

int main() {

  Matrix m1(3, 3);
  Matrix m2(3, 3);
  m1.mat_rand(-10, 10);
  m2.mat_rand(-10, 10);
  Matrix m3(3, 3);
  m1.mat_print();
  std::cout << "\nM2:\n";
  m2.mat_print();
  m3 = m1.mat_mul_adamar(m2);
  m3.mat_print();  
  return 0;
}