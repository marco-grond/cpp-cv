/******************************************************************************
*                               Matrix class                                  *
*                                                                             *
* Allows for the creation of matrices with built in matrix operations. All    *
* data is assumed to be of the type "double".                                 *
*                                                                             *
******************************************************************************/
#include <iostream>
#include <iomanip>
#include <algorithm>

struct index {
  int r;
  int c;
};

class Row;
class Matrix;

class Matrix {
  private:
    int rows;
    int cols;
    double* matrix;

  public:

    // Constructors and destructor
    Matrix(int num_rows, int num_columns);
    Matrix(int num_rows, int num_columns, double data[]);
    ~Matrix();

    // Static methods for instatiating a specific type of matrix
    static Matrix zeros(int num_rows, int num_columns);
    static Matrix identity(int size);
    static Matrix multiply(Matrix left, Matrix right);
    static Matrix add(Matrix left, Matrix right);
    static Matrix subtract(Matrix left, Matrix right);
    static Matrix multiplyElementwise(Matrix left, Matrix right);

    // Functions

    // Getter functions
    int getRows();
    int getColumns();
    Matrix getRow(int row);
    Matrix getColumn(int column);

    void print(int decimals=5);
    Matrix copy();
    void transpose();
    Matrix T();
    struct index minIndex();
    struct index maxIndex();
    double min();
    double max();
    double minRange(int minRow=0, int maxRow=-1, int minCol=0, int maxCol=-1);
    double maxRange(int minRow=0, int maxRow=-1, int minCol=0, int maxCol=-1);
    void resize(int rowLength, int columnLength);
    void concatenate(Matrix mat, int axis=0);


    //int findIndex(double val);
    // TODO - Add matrix functions
    /*
    * Concatenate
    * Append row/column of given row/column vector or of zeros
    * Inverse
    * Resize
    */


    // Operators
    double& operator()(int row, int column);
    Matrix& operator=(Matrix mat);
    Matrix& operator*=(double num);
    Matrix& operator*=(Matrix mat);
    Matrix& operator+=(double num);
    Matrix& operator+=(Matrix mat);
    Matrix& operator-=(double num);
    Matrix& operator-=(Matrix mat);
    Matrix& operator/=(double num);
    Matrix& operator/=(Matrix mat);

    // Friend class
    // Define friend class "Row" to allow for indexing using [][]
    class Row {
      friend class Matrix;
      private:
        Matrix& parent;
        int row;

        Row(Matrix& parent_matrix, int row_index) :
          parent{parent_matrix},
          row(row_index) {};
      public:

        // Get the value at the correct column index
        double& operator[](int column) {
          // Ensure that the index is valid
          if (((-parent.rows > row) || (row >= parent.rows)) ||
              ((-parent.cols > column) || (column >= parent.cols))) {
            std::string index = "(" + std::to_string(row) + "," + 
                                std::to_string(column) + ")";
            std::string size = "(" + std::to_string(parent.rows) + "," + 
                                std::to_string(parent.cols) + ")";
            std::cout << "Invalid index " << index << " for matrix with size " 
                      << size << "\n";
            throw std::invalid_argument("Invalid index.");
          }
 
          // Handle negative indexing
          if (row < 0) {
            row += parent.rows;
          }
          if (column < 0) {
            column += parent.cols;
          }

          return parent.matrix[row*parent.cols + column];
        }
    };

    Row operator[](int row) {
      return Row(*this, row);
    }
};

// Operators functions for acting on matrices
Matrix operator+(Matrix left, Matrix right);
Matrix operator+(Matrix left, double right);
Matrix operator+(double left, Matrix right);
Matrix operator-(Matrix left, Matrix right);
Matrix operator-(Matrix left, double right);
Matrix operator-(double left, Matrix right);
Matrix operator*(Matrix left, Matrix right);
Matrix operator*(Matrix left, double right);
Matrix operator*(double left, Matrix right);
Matrix operator/(Matrix left, Matrix right);
Matrix operator/(Matrix left, double right);
Matrix operator/(double left, Matrix right);
