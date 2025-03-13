#include <string>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

using namespace std;

class MatrixCell {
    public:
        MatrixCell(int value = 0) : m_value {value} {}
        int getValue() const {
            return m_value;
        }
        void setValue(const int value) {
            m_value = value;
        }
    private:
        int m_value;
};

class Matrix {
    public:
        Matrix(int rows, int columns, int value = 0) : m_rows {rows}, m_columns {columns} {
            cout << "Constructor Matrix " << m_rows << "x" << m_columns << endl;
            m_cells = new MatrixCell*[rows];
            for (int i=0; i<rows; i++) {
                m_cells[i] = new MatrixCell[columns] {value};
            }
        }

        Matrix(const Matrix& src) : Matrix {src.m_rows, src.m_columns} { // Copy-Constructor
            cout << "Copy-Constructor Matrix " << m_rows << "x" << m_columns << endl;
            for (int i = 0; i < m_rows; i++) {
                for (int j = 0; j < m_columns; j++) {
                    m_cells[i][j] = src.m_cells[i][j];
                }
            }
        }

        Matrix& operator=(const Matrix& rhs) { // Copy-Assignment
            cout << "Copy-assignment Matrix " << rhs.m_rows << "x" << rhs.m_columns << endl;
            if (this == &rhs) return *this;

            Matrix temp {rhs};
            swap(temp);

            return *this;
        }

        Matrix(Matrix&& src) noexcept { // Move-Constructor
            cout << "Move-Constructor Matrix " << src.m_rows << "x" << src.m_columns << endl;
            // moveFrom(src);
            
            // Other version
            this->swap(src);                    
        }

        Matrix& operator=(Matrix&& rhs) { // move-assignment
            cout << "Move-assignment Matrix " << rhs.m_rows << "x" << rhs.m_columns << endl;

            // if (this == &rhs) return *this;
            // cleanup();
            // moveFrom(rhs);
            // return *this;

            // Other version
            this->swap(rhs);
            return *this;                        
        }

        ~Matrix(){
            cout << "Destructor Matrix: ";
            cleanup();
        }

        void swap(Matrix& rhs) noexcept {
            std::swap(m_rows, rhs.m_rows);
            std::swap(m_columns, rhs.m_columns);
            std::swap(m_cells, rhs.m_cells);
            std::swap(m_name, rhs.m_name);
        }

        void cleanup() noexcept {
            cout << "Deallocate Matrix " << m_rows << "x" << m_columns << endl;
            for (int i = 0; i < m_rows; i++) {
                delete[] m_cells[i];
                m_cells[i] = nullptr;
            }
            
            delete[] m_cells;
            m_cells = nullptr;            
            
            m_rows = 0;
            m_columns = 0;
        }

        // void moveFrom(Matrix& src) noexcept {
        //     // Primitives
        //     m_rows = exchange(src.m_rows, 0);
        //     m_columns = exchange(src.m_columns, 0);
        //     m_cells = exchange(src.m_cells, nullptr);

        //     // Object
        //     m_name = move(src.m_name);
        // }

        int getRows() const {
            return m_rows;
        }
        int getColumns() const {
            return m_columns;
        }
        int getValue(int row, int column) const {
            return m_cells[row][column].getValue();
        }
        void setValue(const int row, const int column, const int value) {
            m_cells[row][column].setValue(value);
        }

    private:
        MatrixCell ** m_cells {nullptr};
        string m_name {""};
        int m_rows {0};
        int m_columns {0};
};

void printMatrix(Matrix matrix) {
    cout << "printMatrix" << endl;
    for (int i = 0; i < matrix.getRows(); i++) {
        for (int j = 0; j < matrix.getColumns(); j++) {
            cout << matrix.getValue(i, j) << " ";
        }
        cout << endl;
    }
}

Matrix matrixRValue(){
    Matrix matrix {1, 1};
    return matrix;
}

class DataMatrix {
    public:
        DataMatrix(int row, int column) : m_matrix {Matrix{row, column}}{}
        // void setData(Matrix matrix) {
        //     m_matrix = move(matrix);
        // }
        void setData(Matrix&& matrix) {
            m_matrix = move(matrix);
        }
        void setData(const Matrix& matrix) {
            m_matrix = matrix;
        }
    private:
        Matrix m_matrix;
};


int main() {  
    DataMatrix data {1, 1};    
    
    cout << "LValue" << endl;
    Matrix matrix3 {3, 3};    
    data.setData(matrix3);

    cout << "RValue" << endl;
    data.setData(Matrix{2, 2});
    return 0;
}