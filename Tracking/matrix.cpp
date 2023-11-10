/******************************************************************************
*                               Matrix class                                  *
*                                                                             *
* Allows for the creation of matrices with built in matrix operations.        *
*                                                                             *
******************************************************************************/
#include "matrix.hpp"

/*
* CONSTRUCTORS AND DESTRUCTOR
*/

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
  //matrix(double[num_rows * num_columns])
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
  //matrix(double[num_rows * num_columns])
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
  //delete matrix;
}

/*
* STATIC METHODS
*/

/*
* Creates a matrix of the given size where every element is set to zero.
*
* num_rows - An integer denoting the number of rows that the matrix should have
* num_columns - An integer denoting the number of columns that the matrix 
*               should have
*/
Matrix Matrix::zeros(int num_rows, int num_columns) {
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
Matrix Matrix::identity(int size) {
  Matrix mat = Matrix::zeros(size, size);
  for (int i = 0; i < size; i++) {
    mat[i][i] = 1;
  }
  return mat;
}

/*
* Applies matrix multiplication to the two matrices presented. Checks are done 
* to ensure that the matrices have the correct dimensions.
* 
* left - A matrix object representing the matrix on the left side for 
*        multiplication
* right - A matrix object representing the matrix on the right side for 
*         multiplication
*/
Matrix Matrix::multiply(Matrix left, Matrix right) {

  // Check to see if the dimensions for the matrices allign
  if (left.getColumns() != right.getRows()) {
    std::cout << "Unable to multiply matrices with incompatible dimensions: ("
              << left.getRows() << ", " << left.getColumns() << ") x ("
              << right.getRows() << ", " << right.getColumns() << ")\n";
    throw std::invalid_argument("Matrix dimension do not match.");
  }

  // Create a new matrix of the correct size and populate
  Matrix result(left.getRows(), right.getColumns());
  double total = 0;
  for (int r = 0; r < left.getRows(); r++) {
    for (int c = 0; c < right.getColumns(); c++) {
      for (int i = 0; i < left.getColumns(); i++) {
        total += left[r][i] * right[i][c];
      }
      result[r][c] = total;
      total = 0;
    }
  }
  return result;
}

/*
* Adds the two matrices together. Checks are done to ensure that the matrices 
* are of the same size.
* 
* left - A matrix object representing the left matrix in the addition
* right - A matrix object representing the right matrix in the addition
*/
Matrix Matrix::add(Matrix left, Matrix right) {
  // Check to ensure that the matrices have the same dimensions
  if ((left.getColumns() != right.getColumns()) || 
      (left.getRows() != right.getRows())) {
    std::cout << "Unable to add matrices with differing dimensions: ("
              << left.getRows() << ", " << left.getColumns() << ") + ("
              << right.getRows() << ", " << right.getColumns() << ")\n";
    throw std::invalid_argument("Matrix dimension do not match.");
  }

  // Create a new matrix of the correct size and populate it
  Matrix result(left.getRows(), left.getColumns());
  for (int r = 0; r < left.getRows(); r++) {
    for (int c = 0; c < left.getColumns(); c++) {
      result[r][c] = left[r][c] + right[r][c];
    }
  }
  return result;
}

/*
* Subtracts the matrix on the right from the matrix on the left. Checks are 
* done to ensure that the matrices are of the same size.
* 
* left - A matrix object representing the left matrix in the subtraction
* right - A matrix object representing the right matrix in the subtraction
*/
Matrix Matrix::subtract(Matrix left, Matrix right) {
  // Check to ensure that the matrices have the same dimensions
  if ((left.getColumns() != right.getColumns()) || 
      (left.getRows() != right.getRows())) {
    std::cout << "Unable to subtract matrices with differing dimensions: ("
              << left.getRows() << ", " << left.getColumns() << ") - ("
              << right.getRows() << ", " << right.getColumns() << ")\n";
    throw std::invalid_argument("Matrix dimension do not match.");
  }

  // Create a new matrix of the correct size and populate it
  Matrix result(left.getRows(), left.getColumns());
  for (int r = 0; r < left.getRows(); r++) {
    for (int c = 0; c < left.getColumns(); c++) {
      result[r][c] = left[r][c] - right[r][c];
    }
  }
  return result;
}

/*
* Performs element-wise multiplication of two matrices. Check are done to 
* ensure that the matrices are of the same size.
*
* left - A matrix object representing the left matrix in the element-wise
*        multiplication.
* right - A matrix object representing the right matrix in the element-wise
*         multiplication
*/
Matrix Matrix::multiplyElementwise(Matrix left, Matrix right) {
  // Check to ensure that the matrices have the same dimensions
  if ((left.getColumns() != right.getColumns()) || 
      (left.getRows() != right.getRows())) {
    std::cout << "Unable to perform element-wise multiplication on matrices "
              << "with differing dimensions: (" << left.getRows() << ", " 
              << left.getColumns() << ") - (" << right.getRows() << ", " 
              << right.getColumns() << ")\n";
    throw std::invalid_argument("Matrix dimension do not match.");
  }

  // Create a new matrix of the correct size and populate it
  Matrix result(left.getRows(), left.getColumns());
  for (int r = 0; r < left.getRows(); r++) {
    for (int c = 0; c < left.getColumns(); c++) {
      result[r][c] = left[r][c] * right[r][c];
    }
  }
  return result;
}

/*
* PUBLIC METHODS
*/

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
* Extracts a single row from the matrix and returns that as a new matrix.
*
* row - The integer index of the row that is to be extracted
*/
Matrix Matrix::getRow(int row) {

  // Check to ensure that a valid row is requested
  if ((row < 0) || (row >= rows)) {
    std::cout << "Invalid row index " << row << " for matrix with "<< rows 
              << " rows\n";
    throw std::invalid_argument("Invalid row index.");
  }

  // Create a new matrix for the extracted row and return that
  Matrix newMatrix(1, cols);
  for (int i = 0; i < cols; i++) {
    newMatrix[0][i] = matrix[row*cols + i];
  }
  return newMatrix;
}

/*
* Extracts a single column from the matrix and returns that as a new matrix.
*
* column - The integer index of the column that is to be extracted
*/
Matrix Matrix::getColumn(int column) {

  // Check to ensure that a valid column is requested
  if ((column < 0) || (column >= cols)) {
    std::cout << "Invalid column index " << column << " for matrix with "
              << cols << " columns\n";
    throw std::invalid_argument("Invalid column index.");
  }

  // Create a new matrix for the extracted column and return that
  Matrix newMatrix(rows, 1);
  for (int i = 0; i < rows; i++) {
    newMatrix[i][0] = matrix[i*cols + column];
  }
  return newMatrix;
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

/*
* Find the transpose of the current matrix. This operation is done in place.
*/
void Matrix::transpose() {
  int temp;
  // Check if matrix is square, in which case swap relevant positions
  if (rows == cols) {
    for (int i = 0; i < rows; i++) {
      for (int j = i+1; j < cols; j++) {
        temp = matrix[i*rows + j];
        matrix[i*cols + j] = matrix[j*cols + i];
        matrix[j*cols + i] = temp;
      }
    }

  // If the matrix is not square, create and populate a new matrix
  } else {
    double tempMat[rows * cols];
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        tempMat[j*rows + i] = matrix[i*cols + j];
      }
    }
    for (int i = 0; i < (rows*cols); i++) {
      matrix[i] = tempMat[i];
    }
    temp = rows;
    rows = cols;
    cols = temp;

  }
}

/*
* Find and return the transpose of the matrix
*/
Matrix Matrix::T() {
  Matrix newMat = copy();
  newMat.transpose();
  return newMat;
}

/*
* Finds the index (row, column) of the minimum value in the matrix. If multiple 
* items have the same value, the first instance in row major order is returned.
* Returns an index struct where index.r gives the row index and index.c gives 
* the column index.
*/
struct index Matrix::minIndex() {

  // Find the minimum value in the array
  int arrIndex = 0;
  for (int i = 0; i < (rows*cols); i++) {
    if (matrix[i] < matrix[arrIndex]) {
      arrIndex = i;
    }
  }

  // Translate the minimum value 
  struct index returnIndex;
  returnIndex.r = arrIndex/cols;
  returnIndex.c = arrIndex%cols;
  return returnIndex;
}

/*
* Finds the index (row, column) of the maximum value in the matrix. If multiple 
* items have the same value, the first instance in row major order is returned.
* Returns an index struct where index.r gives the row index and index.c gives 
* the column index.
*/
struct index Matrix::maxIndex() {

  // Find the maximum value in the array
  int arrIndex = 0;
  for (int i = 0; i < (rows*cols); i++) {
    if (matrix[i] > matrix[arrIndex]) {
      arrIndex = i;
    }
  }

  // Translate the minimum value 
  struct index returnIndex;
  returnIndex.r = arrIndex/cols;
  returnIndex.c = arrIndex%cols;
  return returnIndex;
}

/*
* Finds and returns the minimum value in the matrix.
*/
double Matrix::min() {
  struct index arrIndex= minIndex();
  return matrix[arrIndex.r*cols + arrIndex.c];
}

/*
* Finds and return the maximum value in the matrix.
*/
double Matrix::max() {
  struct index arrIndex= maxIndex();
  return matrix[arrIndex.r*cols + arrIndex.c];
}

/*
* PUBLIC OPERATOR METHODS
*/

/*
* Allows indexing using (row, column) into the matrix. Index must exist within 
* the size of the matrix.
*/
double& Matrix::operator()(int row, int column) {
      //std::cout << "(" << row << ", " << column << ") -> (" << rows << ", " << cols << ") " << (((0 > row) || (row >= rows)) || ((0 > column) || (column >= cols)))  << "\n";
      if (((0 > row) || (row >= rows)) ||
          ((0 > column) || (column >= cols))) {
        std::string index = "(" + std::to_string(row) + "," + 
                            std::to_string(column) + ")";
        std::string size = "(" + std::to_string(rows) + "," + 
                            std::to_string(cols) + ")";
        std::cout << "Invalid index " << index << " for matrix with size " 
                  << size << "\n";
        throw std::invalid_argument("Invalid index.");
      }

      return matrix[row*cols + column];
    }

/*
* Replaces the current instance of the class with the given one.
*/
Matrix& Matrix::operator=(Matrix mat) {

  // If assigned to the same pointer, nothing needs to be done
  if (this == &mat) {
    return *this;
  }

  // If the rows and columns do not match up, need to create a new matrix.
  if ((rows != mat.getRows()) || (cols != mat.getColumns())) {
    rows = mat.getRows();
    cols = mat.getColumns();
    //delete matrix;
    double matrix[rows*cols];
  }

  // Update the values in matrix.
  for (int i = 0; i < rows; i ++) {
    for (int j = 0; j < cols; j++) {
      matrix[i*cols + j] = mat[i][j];
    }
  }
  return *this;
}

/*
* Multiplies every value in the matrix by the given value.
*/
Matrix& Matrix::operator*=(double num) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i*cols + j] *= num;
    }
  }
  return *this;
}

/*
* Perform matrix multiplication with the given matrix.
*/
Matrix& Matrix::operator*=(Matrix mat) {
  Matrix multiplied = multiply(*this, mat);
  return (*this = multiplied);
}

/*
* Adds the given value to every value in the matrix.
*/
Matrix& Matrix::operator+=(double num) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i*cols + j] += num;
    }
  }
  return *this;
}

/*
* Perform matrix addition with the given matrix.
*/
Matrix& Matrix::operator+=(Matrix mat) {
  Matrix added = add(*this, mat);
  return (*this = added);
}

/*
* Subtracts the given value from every value in the matrix.
*/
Matrix& Matrix::operator-=(double num) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i*cols + j] -= num;
    }
  }
  return *this;
}

/*
* Perform matrix subtraction with the given matrix.
*/
Matrix& Matrix::operator-=(Matrix mat) {
  Matrix added = subtract(*this, mat);
  return (*this = added);
}

// Operator functions for acting on matrices

/*
* Adds two matrices together
*/
Matrix operator+(Matrix left, Matrix right) {
  Matrix newMat = left.copy();
  newMat += right;
  return newMat;
}

/*
* Adds a matrix and a number together
*/
Matrix operator+(Matrix left, double right) {
  Matrix newMat = left.copy();
  newMat += right;
  return newMat;
}

/*
* Adds a matrix and a number together
*/
Matrix operator+(double left, Matrix right) {
  Matrix newMat = right.copy();
  newMat += left;
  return newMat;
}

/*
* Subtracts the matrix on the right from the matrix on the left
*/
Matrix operator-(Matrix left, Matrix right) {
  Matrix newMat = left.copy();
  newMat -= right;
  return newMat;
}

/*
* Subtracts the number on the right from the matrix on the left
*/
Matrix operator-(Matrix left, double right) {
  Matrix newMat = left.copy();
  newMat -= right;
  return newMat;
}

/*
* Subtracts the matrix on the right from the number on the left
*/
Matrix operator-(double left, Matrix right) {
  Matrix newMat = right.copy();
  newMat *= -1;
  newMat += left;
  return newMat;
}

/*
* Multiply the matrices together
*/
Matrix operator*(Matrix left, Matrix right) {
  Matrix newMat = left.copy();
  newMat *= right;
  return newMat;
}

/*
* Multiply the matrix with the given number
*/
Matrix operator*(Matrix left, double right) {
  Matrix newMat = left.copy();
  newMat *= right;
  return newMat;
}

/*
* Multiply the matrix with the given number
*/
Matrix operator*(double left, Matrix right) {
  Matrix newMat = right.copy();
  newMat *= left;
  return newMat;
}
