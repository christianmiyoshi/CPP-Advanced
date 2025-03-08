#include <string>
#include <iostream>
#include <memory>
#include <utility>

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
        Matrix(int rows, int columns) : m_rows {rows}, m_columns {columns} {
            cout << "Constructor Matrix " << m_rows << "x" << m_columns << endl;
            m_cells = new MatrixCell*[rows];
            for (int i=0; i<rows; i++) {
                m_cells[i] = new MatrixCell[columns];
            }
        }
        Matrix(const Matrix& src) : Matrix {src.m_rows, src.m_columns} { // copy-constructor
            cout << "Copy-Constructor Matrix " << m_rows << "x" << m_columns << endl;
            for (int i = 0; i < m_rows; i++) {
                for (int j = 0; j < m_columns; j++) {
                    m_cells[i][j] = src.m_cells[i][j];
                }
            }
        }

        void swap(Matrix& rhs) noexcept {
            std::swap(m_rows, rhs.m_rows);
            std::swap(m_columns, rhs.m_columns);
            std::swap(m_cells, rhs.m_cells);
        }

        Matrix& operator=(const Matrix& rhs) { // copy-assignment
            cout << "Copy-assignment Matrix " << rhs.m_rows << "x" << rhs.m_columns << endl;
            if (this == &rhs) return *this;

            Matrix temp {rhs};
            swap(temp);

            return *this;
        }

        ~Matrix(){
            cout << "Destructor Matrix: ";
            deallocateCells();
        }
        void deallocateCells() {
            cout << "Deallocate Matrix " << m_rows << "x" << m_columns << endl;
            for (int i = 0; i < m_rows; i++) {
                delete[] m_cells[i];
                m_cells[i] = nullptr;
            }
            delete[] m_cells;
            m_cells = nullptr;  
        }
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
        MatrixCell ** m_cells;
        int m_rows {0};
        int m_columns {0};
};

void printMatrix(const Matrix matrix) {
    cout << "printMatrix" << endl;
    for (int i = 0; i < matrix.getRows(); i++) {
        for (int j = 0; j < matrix.getColumns(); j++) {
            cout << matrix.getValue(i, j) << " ";
        }
        cout << endl;
    }
}

int main() {
    Matrix matrix {3, 4};
    matrix.setValue(1, 1, 1);
    printMatrix(matrix);    

    // Matrix matrixCopy {2, 2};
    // matrixCopy.setValue(1, 1, 2);
    // matrixCopy = matrix;


    cout << "End program" << endl;
    return 0;
}