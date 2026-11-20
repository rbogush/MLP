#include "matrix.hpp"
#include "activate_func.hpp"

int main() {

  Matrix m1({{1, 2, 3, 4}});
  m1.mat_print();  
  std::cout << "\nM2:\n";
  Matrix m2(5,1);
  m2 = Activate_function(m1, SOFTMAX);
  m2.mat_print();  
  return 0;
}