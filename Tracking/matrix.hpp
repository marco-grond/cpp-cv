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
    Matrix(int num_rows, int num_columns, double* data);
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

    //int findIndex(double val);
    // TODO - Add matrix functions
    /*
    * Min - entire, rows, columns
    * Max - entire, rows, columns
    * Inverse
    * Element wise division
    */


    // Operators
    double& operator()(int row = 0, int column = 0);
    Matrix& operator=(Matrix mat);
    Matrix& operator*=(double num);
    Matrix& operator*=(Matrix mat);
    Matrix& operator+=(double num);
    Matrix& operator+=(Matrix mat);
    Matrix& operator-=(double num);
    Matrix& operator-=(Matrix mat);

    //Matrix operator+();
    //Matrix operator-();

    // Friend class
    // Define friend class "Row" to allow for indexing using []
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
          //std::cout << "[" << row << "][" << column << "] -> (" << parent.rows << ", " << parent.cols << ")\n";
          if (((0 > row) || (row >= parent.rows)) ||
              ((0 > column) || (column >= parent.cols))) {
            std::string index = "(" + std::to_string(row) + "," + 
                                std::to_string(column) + ")";
            std::string size = "(" + std::to_string(parent.rows) + "," + 
                                std::to_string(parent.cols) + ")";
            std::cout << "Invalid index " << index << " for matrix with size " 
                      << size << "\n";
            throw std::invalid_argument("Invalid index.");
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
