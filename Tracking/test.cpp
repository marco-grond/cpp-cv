#include <iostream>

#include "matrix.hpp"

int main() {
  double a[2][3] = {{1, 2, 3}, 
                      {3, 4, 5}};
  std::cout << sizeof(a)/sizeof(a[0]) << "\n";
  std::cout << sizeof(a[0])/sizeof(double) << "\n";

  //Matrix mat = Matrix::zeros(3, 4);
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

  Matrix mat2 = Matrix::zeros(3, 4);
  mat2.print(5);
  std::cout << "\n";

  Matrix mat3 = Matrix::identity(5);
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
  mat4.print();
  std::cout << "\n";

  Matrix column = mat4.getColumn(2);
  column.print();
  std::cout << "\n";

  std::cout << "\n\nMultiplication testing:\n";
  Matrix row = mat4.getRow(2);
  row.print();
  std::cout << "\n";
  row *= 5;
  row.print();
  row *= 2.5;
  row.print();
  Matrix test = Matrix::multiply(row, column);
  test.print();
  //row *= column;
  //row.print();
  column *= row;
  column.print();
  mat *= mat2;
  mat.print();

  std::cout << "\n\nDivision testing:\n";
  Matrix matDivision = mat4.copy();
  matDivision.print();
  matDivision /= 2;
  matDivision.print();
  matDivision /= mat4;
  matDivision.print();
  Matrix matTest = matDivision / 4.0;
  matTest.print();
  matTest = 1 / matTest;
  matTest.print();
  matTest = matTest / mat4;
  matTest.print();

  std::cout << "\n\nAddition testing:\n";
  mat4.print();
  mat4 += 5;
  mat4.print();
  mat4 += 1.5;
  mat4.print();
  mat4 += mat3;//Matrix::add(mat4, mat3);
  mat4.print();

  std::cout << "\n\nSubtraction testing:\n";
  mat4 -= 5;
  mat4.print();
  mat4 -= 1.5;
  mat4.print();
  mat4 -= mat3;//Matrix::subtract(mat4, mat3);
  mat4.print();

  std::cout << "\n\nElement-wise multiplication:\n";
  mat4 += 2;
  mat3 *= 2;
  mat4.print();
  mat3.print();
  mat4 = Matrix::multiplyElementwise(mat4, mat3);
  mat4.print();

  std::cout << "\n\n+ Operator:\n";
  mat4 = mat4 + mat3;
  mat4.print();
  mat4 = mat4 + 3;
  mat4.print();
  mat4 = 2.5 + mat4;
  mat4.print();

  std::cout << "\n\n- Operator:\n";
  mat4 = mat4 - mat3;
  mat4.print();
  mat4 = mat4 - 2.5;
  mat4.print();
  mat4 = 2 - mat4;
  mat4.print();
  mat4 = -1 - mat4;
  mat4.print();

  std::cout << "\n\n* Operator:\n";
  mat4 = mat4 * mat3;
  mat4.print();
  mat4 = mat4 * 2;
  mat4.print();
  mat4 = 0.5 * mat4;
  mat4.print();

  std::cout << "\n\nTranspose:\n";
  Matrix mat5 = Matrix(3, 2);
  int k = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      mat5[i][j] = k;
      k++;
    }
  }
  mat5.print();
  mat5.transpose();
  mat5.print();
  mat5 = mat5.T();
  mat5.print();

  std::cout << "\n\nTest min and minIndex:\n";
  mat5.print();
  struct index ind = mat5.minIndex();
  double val = mat5.min();
  std::cout << "Min Index: (" << ind.r << ", " << ind.c << ")\n";
  std::cout << "Min Value: " << val << "\n";
  mat5.transpose();
  mat5.print();
  ind = mat5.minIndex();
  val = mat5.min();
  std::cout << "Min Index: (" << ind.r << ", " << ind.c << ")\n";
  std::cout << "Min Value: " << val << "\n";
  mat5.transpose();

  std::cout << "\n\nTest max and maxIndex:\n";
  mat5.print();
  ind = mat5.maxIndex();
  val = mat5.max();
  std::cout << "Max Index: (" << ind.r << ", " << ind.c << ")\n";
  std::cout << "Max Value: " << val << "\n";
  mat5.transpose();
  mat5.print();
  ind = mat5.maxIndex();
  val = mat5.max();
  std::cout << "Max Index: (" << ind.r << ", " << ind.c << ")\n";
  std::cout << "Max Value: " << val << "\n";
  mat5.transpose();

  std::cout << "\n\nTest negative indexing:\n";
  mat5.print();
  std::cout << "mat[0][-1]: " << mat5[0][-1] << "\n";
  std::cout << "mat[-1][0]: " << mat5[-1][0] << "\n";
  std::cout << "mat[-3][-2]: " << mat5[-3][-2] << "\n";
  std::cout << "mat(-1, 0): " << mat5(-1, 0) << "\n";
  std::cout << "mat(0, -1): " << mat5(0, -1) << "\n";
  std::cout << "mat(-3, -2): " << mat5(-3, -2) << "\n";

  std::cout << "\n\nTest min and max in range:\n";
  mat5.print();
  std::cout << "Min full range: " << mat5.minRange() << "\n";
  std::cout << "Max full range: " << mat5.maxRange() << "\n";
  std::cout << "Min [1:2, 0:1]: " << mat5.minRange(1, 2, 0, 1) << "\n";
  std::cout << "Max [0:1, 0:0]: " << mat5.maxRange(0, 1, 0, 0) << "\n";
  std::cout << "Min [-1:-1, -1:-1]: " << mat5.minRange(-1, -1, -1, -1) << "\n";
  std::cout << "Max [1:1, 1:1]: " << mat5.maxRange(1, 1, 1, 1) << "\n";
  
  std::cout << "\n\nTest resizing:\n";
  mat5.print();
  mat5.resize(6, 1);
  mat5.print();
  mat5.resize(2, 3);
  mat5.print();
  mat5.resize(1, 6);
  mat5.print();
  mat5.resize(3, 2);
  mat5.print();
  /*mat5.resize(3, 3);
  mat5.print();*/

  std::cout << "\n\nTest concatenation:\n";
  mat5.print();
  double b[6] = {6, 7, 8, 9, 10, 11};
  Matrix mat6(3, 2, b);
  mat6.print();
  mat5.concatenate(mat6, 1);
  mat5.print();
  mat6.resize(6, 1);
  mat5.concatenate(mat6, 0);
  mat5.print();
  mat5.concatenate(mat5);
  mat5.print();
}
