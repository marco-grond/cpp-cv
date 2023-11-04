#include <iostream>

#include "matrix.hpp"

int main() {
  double a[2][3] = {{1, 2, 3}, 
                      {3, 4, 5}};
  std::cout << sizeof(a)/sizeof(a[0]) << "\n";
  std::cout << sizeof(a[0])/sizeof(double) << "\n";

  //Matrix mat = Matrix::Zeros(3, 4);
  Matrix mat(2, 3);
  mat.print(5);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      //std::cout << "ccc\n";
      mat[i][j] = 3*i + j;
    }
  }
  mat.print(5);
  std::cout << "\n";

  Matrix mat2 = Matrix::Zeros(3, 4);
  mat2.print(5);
  std::cout << "\n";

  Matrix mat3 = Matrix::Identity(5);
  mat3.print();
  std::cout << "\n";

  mat3[2][2] = 3;
  mat3.print();
  std::cout << "\n";

  Matrix mat4 = mat3.copy();
  mat3[2][2] = 9;
  mat3.print();
  mat4.print();
  std::cout << "\n";

  std::cout << mat4[2][2] << "\n";
  std::cout << mat4(2, 2) << "\n";
  std::cout << mat4(6, 1);
}
