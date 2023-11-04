/******************************************************************************
*                               Matrix class                                  *
*                                                                             *
* Allows for the creation of matrices with built in matrix operations.        *
*                                                                             *
******************************************************************************/
#include "matrix.hpp"

// Constructors and destructor
/*
* Basic constructor for empty matrix.
*
* num_rows - An integer denoting the number of rows that the matrix should have
* num_columns - An integer denoting the number of columns that the matrix 
*               should have
*/
Matrix::Matrix(int num_rows, int num_columns) :
  rows(num_rows),
  cols(num_columns),
  matrix(new double[num_rows * num_columns])
{}

/* 
* Constructor for creating a Matrix and filling it with the provided data.
*
* num_rows - An integer denoting the number of rows that the matrix should have
* num_columns - An integer denoting the number of columns that the matrix 
*               should have
* data - A pointer to a datastructure of the correct type containing the data 
*        that the matrix should be filled with in row major order
*/
Matrix::Matrix(int num_rows, int num_columns, double* data) :
  rows(num_rows),
  cols(num_columns),
  matrix(new double[num_rows * num_columns])
{
  if ((sizeof(data)/sizeof(double)) != (rows * cols)) {
    throw std::invalid_argument("Data size does not match the dimension"); 
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i*cols + j] = data[i*cols + j];
    }
  }
}

/*
* Deconstructor for the Matrix class to remove the array used to represent the 
* matrix.
*/
Matrix::~Matrix() {
  delete matrix;
}

// Functions

/*
* Creates a matrix of the given size where every element is set to zero.
*
* num_rows - An integer denoting the number of rows that the matrix should have
* num_columns - An integer denoting the number of columns that the matrix 
*               should have
*/
Matrix Matrix::Zeros(int num_rows, int num_columns) {
  Matrix mat(num_rows, num_columns);
  for (int i = 0; i < num_rows; i++){
    for (int j = 0; j < num_columns; j++) {
      mat[i][j] = 0;
    }
  }
  return mat;
}

/*
* Creates a (size x size) identity matrix (all elements are 0, except the 
* diagonal which is set to 1)
*
* size - An integer denoting the number of rows and columns for the matrix
*/
Matrix Matrix::Identity(int size) {
  Matrix mat = Matrix::Zeros(size, size);
  for (int i = 0; i < size; i++) {
    mat[i][i] = 1;
  }
  return mat;
}

/*
* Prints out the values of the matrix to the console
*
* decimals - The precision of the numbers that should be printed. Default 5
*/
void Matrix::print(int decimals) {
  std::cout << std::fixed;
  std::cout << std::setprecision(decimals);
  std::cout << "([";
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++) {
      std::cout << matrix[i*cols + j];
      if (j != (cols - 1)) {
        std::cout << ", ";
      }
    }
    if (i != (rows - 1)) {
      std::cout << "],\n  ";
    } else {
      std::cout << "]";
    }
  }
  std::cout << "], (" << rows << ", " << cols << "))\n";
}

/*
* Returns the number of rows in the matrix.
*/
int Matrix::getRows() {
  return rows;
}

/*
* Returns the number of columns in the matrix.
*/
int Matrix::getColumns() {
  return cols;
}

/*
* Creates a copy of this matrix and passes it back. 
*/
Matrix Matrix::copy() {
  Matrix newMatrix(rows, cols);
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++) {
      newMatrix[i][j] = matrix[i*cols + j];
    }
  }
  return newMatrix;
}
