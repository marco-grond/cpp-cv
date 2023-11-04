/******************************************************************************
*                               Matrix class                                  *
*                                                                             *
* Allows for the creation of matrices with built in matrix operations. All    *
* data is assumed to be of the type "double".                                 *
*                                                                             *
******************************************************************************/
#include <iostream>
#include <iomanip>

class Row;
class Matrix;

class Matrix {
  private:
    int const rows;
    int const cols;
    double* matrix;

  public:

    // Constructors and destructor
    Matrix(int num_rows, int num_columns);
    Matrix(int num_rows, int num_columns, double* data);
    ~Matrix();

    // Static methods for instatiating a specific type of matrix
    static Matrix Zeros(int num_rows, int num_columns);
    static Matrix Identity(int size);

    // Functions
    void print(int decimals=5);
    int getRows();
    int getColumns();
    Matrix copy();
    // TODO - Add matrix functions

    // Operators
    double &operator()(int row = 0, int column = 0 ) {
      std::cout << "(" << row << ", " << column << ") -> (" << rows << ", " << cols << ") " << (((0 > row) || (row >= rows)) || ((0 > column) || (column >= cols)))  << "\n";
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
          std::cout << "[" << row << "][" << column << "] -> (" << parent.rows << ", " << parent.cols << ")\n";
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
