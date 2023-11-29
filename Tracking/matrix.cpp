/******************************************************************************
*                               Matrix class                                  *
*                                                                             *
* Allows for the creation of matrices with built in matrix operations.        *
*                                                                             *
******************************************************************************/
#include "matrix.hpp"

/******************************************************************************
* CONSTRUCTORS AND DESTRUCTOR                                                 *
******************************************************************************/

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
Matrix::Matrix(int num_rows, int num_columns, double data[]) :
  rows(num_rows),
  cols(num_columns),
  //matrix(double[num_rows * num_columns])
  matrix(new double[num_rows * num_columns])
{
  /*if ((sizeof(data)/sizeof(double)) != (rows * cols)) {
    throw std::invalid_argument("Data size does not match the dimension"); 
  }*/
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

/******************************************************************************
* STATIC METHODS                                                              *
******************************************************************************/

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

/******************************************************************************
* PUBLIC METHODS                                                              *
******************************************************************************/

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
* Finds and returns the minimum value in a given range of the matrix. The 
* arguments indicate both the row and column range.
*
* minRow - The lower bound row index for the function
* minCol - The lower bound column index for the function
* maxRow - The upper bound row index for the function
* maxCol - The upper bound column index for the function
*/
double Matrix::minRange(int minRow, int maxRow, int minCol, int maxCol) {
  // Handle negative indexing
  if (maxRow < 0) {
    maxRow += rows;
  }
  if (maxCol < 0) {
    maxCol += cols;
  }
  if (minRow < 0) {
    minRow += rows;
  }
  if (minCol < 0) {
    minCol += cols;
  }

  // Ensure that the range is valid
  if (((minRow < 0) || (maxRow >= rows) || (minRow > maxRow)) ||
      ((minCol < 0) || (maxCol >= cols) || (minCol > maxCol))) {
    std::string slice = "(" + std::to_string(minRow) + ":" + 
                        std::to_string(maxRow) + ", " +
                        std::to_string(minCol) + ":" + 
                        std::to_string(maxCol) + ")";
    std::string size = "(" + std::to_string(rows) + "," + 
                        std::to_string(cols) + ")";
    std::cout << "Invalid range " << slice << " for matrix with size " 
              << size << "\n";
    throw std::invalid_argument("Invalid index.");
  }

  // Find the minimum in the range and return it
  int arrIndex = minRow*cols + minCol;
  for (int i = minRow; i <= maxRow; i++) {
    for (int j = minCol; j <= maxCol; j++) {
      if (matrix[i*cols + j] < matrix[arrIndex]) {
        arrIndex = i*cols + j;
      }
    }
  }
  return matrix[arrIndex];
}

double Matrix::maxRange(int minRow, int maxRow, int minCol, int maxCol) {
  // Handle negative indexing
  if (maxRow < 0) {
    maxRow += rows;
  }
  if (maxCol < 0) {
    maxCol += cols;
  }
  if (minRow < 0) {
    minRow += rows;
  }
  if (minCol < 0) {
    minCol += cols;
  }

  // Ensure that the range is valid
  if (((minRow < 0) || (maxRow >= rows) || (minRow > maxRow)) ||
      ((minCol < 0) || (maxCol >= cols) || (minCol > maxCol))) {
    std::string slice = "(" + std::to_string(minRow) + ":" + 
                        std::to_string(maxRow) + ", " +
                        std::to_string(minCol) + ":" + 
                        std::to_string(maxCol) + ")";
    std::string size = "(" + std::to_string(rows) + "," + 
                        std::to_string(cols) + ")";
    std::cout << "Invalid range " << slice << " for matrix with size " 
              << size << "\n";
    throw std::invalid_argument("Invalid index.");
  }

  // Find the maximum in the range and return it
  int arrIndex = minRow*cols + minCol;
  for (int i = minRow; i <= maxRow; i++) {
    for (int j = minCol; j <= maxCol; j++) {
      if (matrix[i*cols + j] > matrix[arrIndex]) {
        arrIndex = i*cols + j;
      }
    }
  }
  return matrix[arrIndex];
}

/*
* Resizes the matrix to the given sizes. Resizing is done on a row-major order
* basis. Checks to ensure that the new size is compatible with the original 
* size.
*/
void Matrix::resize(int rowLength, int columnLength) {
  if ((rowLength * columnLength) != (rows * cols)) {
    std::string newDims = "(" + std::to_string(rowLength) + ", " + 
                          std::to_string(columnLength) + ")";
    std::string oldDims = "(" + std::to_string(rows) + ", " + 
                          std::to_string(cols) + ")";
    std::cout << "Invalid resizing dimensions " << oldDims << " to " 
              << newDims << "\n";
    throw std::invalid_argument("Incompatible resizing dimensions.");
  }
  rows = rowLength;
  cols = columnLength;
}

/*
* Concatenate the provided matrix to the current matrix if the dimensions 
* match along the provided axis.
*
* mat - The matrix which should be concatenated with the current matrix
* axis - The axis on which concatenation should be done. If set to 0, mat will
*        be added to the right of the currect matrix, extending the rows. If 
*        set to 1, mat will be added to the bottom of the current matrix 
*        extending the columns
*/
void Matrix::concatenate(Matrix mat, int axis) {

  // Check to ensure that the provided axis is valid
  if ((axis < 0) || (axis > 1)) {
    std::cout << "Invalid concatenate axis: " << axis << ". Must be 0 or 1.\n";
    throw std::invalid_argument("Invalid axis for concatenation.");
  }

  // Check to ensure that the provided matrix is of the correct shape
  if (((axis == 0) && (mat.getRows() != rows)) || 
      ((axis == 1) && mat.getColumns() != cols)){
    std::cout << "Invalid matrix shapes (" << rows << "," << cols <<") and (" 
              << mat.getRows() << ", " << mat.getColumns() 
              << ") for concatenation on axis " << axis << ".\n";
    throw std::invalid_argument("Invalid matrix sizes for concatenation.");
  }

  // Create a new array to store the matrix, change the number of columns and 
  // fill the array with values from both matrices. Column
  if (axis == 0) {
    int newColumns = cols + mat.getColumns();
    double* temp = new double[rows * newColumns];
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        temp[i*newColumns + j] = matrix[i*cols + j];
      }
    }
    for (int i = 0; i < mat.getRows(); i++) {
      for (int j = 0; j < mat.getColumns(); j++) {
        temp[i*newColumns + j + cols] = mat[i][j];
      }
    }
    cols = newColumns;
    delete matrix;
    matrix = temp;

  // Create a new array to store the matrix, change the number of rows and fill
  // the array with values from both matrices
  } else {
    int newRows = rows + mat.getRows();
    double* temp = new double[newRows * cols];
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        temp[i*cols + j] = matrix[i*cols + j];
      }
    }
    for (int i = 0; i < mat.getRows(); i++) {
      for (int j = 0; j < mat.getColumns(); j++) {
        std::cout << "(" << i << ", " << j << "): ";
        std::cout << ((i+newRows)*cols + j) << " -> " << mat[i][j] << "\n";
        temp[(i+rows)*cols + j] = mat[i][j];
      }
    }
    rows = newRows;
    delete matrix;
    matrix = temp;
  }
}

/******************************************************************************
* PUBLIC OPERATOR METHODS                                                     *
******************************************************************************/

/*
* Allows indexing using (row, column) into the matrix. Index must exist within 
* the size of the matrix.
*/
double& Matrix::operator()(int row, int column) {
  // Ensure that the index is valid
  if (((-rows > row) || (row >= rows)) ||
      ((-cols > column) || (column >= cols))) {
    std::string index = "(" + std::to_string(row) + "," + 
                        std::to_string(column) + ")";
    std::string size = "(" + std::to_string(rows) + "," + 
                        std::to_string(cols) + ")";
    std::cout << "Invalid index " << index << " for matrix with size " 
              << size << "\n";
    throw std::invalid_argument("Invalid index.");
  }

  // Handle negative indexing
  if (row < 0) {
    row += rows;
  }
  if (column < 0) {
    column += cols;
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
* Performs matrix subtraction with the given matrix.
*/
Matrix& Matrix::operator-=(Matrix mat) {
  Matrix added = subtract(*this, mat);
  return (*this = added);
}

/*
* Divides every element in the matrix by the given number value
*/
Matrix& Matrix::operator/=(double num) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i*cols + j] /= num;
    }
  }
  return *this;
}

/*
* Divides every element in the matrix by the corresponding element in the 
* provided matrix. The matrices have to have the same shape.
*/
Matrix& Matrix::operator/=(Matrix mat) {
  // If the rows and columns do not match up, need to create a new matrix.
  if ((rows != mat.getRows()) || (cols != mat.getColumns())) {
    std::string dim1 = "(" + std::to_string(rows) + "," + 
                       std::to_string(cols) + ")";
    std::string dim2 = "(" + std::to_string(mat.getRows()) + "," + 
                        std::to_string(mat.getColumns()) + ")";
    std::cout << "Mismatched sizes for matrices with dimensions: " << dim1
              << " and " << dim2 << "\n";
    throw std::invalid_argument("Mismatched matrix dimensions.");
  }

  // Subtract the matrices from one another and return
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix[i*cols + j] /= mat[i][j];
    }
  }
  return *this;
}

/******************************************************************************
 * Operator functions for acting on matrices                                  *
/******************************************************************************

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

/*
* Does element wise division on the two matrices. The matrices must have the 
* same dimentions.
*/
Matrix operator/(Matrix left, Matrix right) {
  Matrix newMat = left.copy();
  newMat /= right;
  return newMat;
}

/*
* Divides the matrix by the given number.
*/
Matrix operator/(Matrix left, double right) {
  Matrix newMat = left.copy();
  newMat /= right;
  return newMat;
}

/*
* Returns a matrix where each element is equal to the number value divided by
* the corresponding element in the given matrix.
*/
Matrix operator/(double left, Matrix right) {
  Matrix newMat = right.copy();
  for (int i = 0; i < newMat.getRows(); i++) {
    for (int j = 0; j < newMat.getColumns(); j++) {
      newMat[i][j] = left/newMat[i][j];
    }
  }
  return newMat;
}
