#include <iostream>
#include <fstream>
using namespace std;

class Matrix {
public:
    int matrix_size;
    double** matrix_data;

    Matrix(int size = 0) : matrix_size(size) {
        matrix_data = new double*[matrix_size];
        for (int i = 0; i < matrix_size; ++i) {
            matrix_data[i] = new double[matrix_size]();
        }
    }

    // Copy constructor for deep copying
    Matrix(const Matrix& other) : matrix_size(other.matrix_size) {
        matrix_data = new double*[matrix_size];
        for (int i = 0; i < matrix_size; ++i) {
            matrix_data[i] = new double[matrix_size];
            for (int j = 0; j < matrix_size; ++j) {
                matrix_data[i][j] = other.matrix_data[i][j];
            }
        }
    }

    // Destructor
    ~Matrix() {
        for (int i = 0; i < matrix_size; ++i) {
            delete[] matrix_data[i];
        }
        delete[] matrix_data;
    }

    // Assignment operator for deep copy
    Matrix& operator=(const Matrix& other) {
        if (this == &other) return *this; // Self-assignment check

        // Clean up old memory
        for (int i = 0; i < matrix_size; ++i) {
            delete[] matrix_data[i];
        }
        delete[] matrix_data;

        // Copy new data
        matrix_size = other.matrix_size;
        matrix_data = new double*[matrix_size];
        for (int i = 0; i < matrix_size; ++i) {
            matrix_data[i] = new double[matrix_size];
            for (int j = 0; j < matrix_size; ++j) {
                matrix_data[i][j] = other.matrix_data[i][j];
            }
        }

        return *this;
    }
};

// Function to read matrix data from a file
void read_matrix_from_file(const string& file_name, Matrix& matrix_1, Matrix& matrix_2) {
    std::ifstream file(file_name);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    int size;
    file >> size;
    matrix_1 = Matrix(size);
    matrix_2 = Matrix(size);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            file >> matrix_1.matrix_data[i][j];
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            file >> matrix_2.matrix_data[i][j];
        }
    }
    file.close();
}

// Function to print a single matrix
void print_matrix(const Matrix& matrix) {
    for (int i = 0; i < matrix.matrix_size; ++i) {
        for (int j = 0; j < matrix.matrix_size; ++j) {
            cout << matrix.matrix_data[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to print both matrices
void print_matrix(const Matrix& matrix_1, const Matrix& matrix_2) {
    cout << "Matrix 1 ->" << endl;
    print_matrix(matrix_1);
    cout << "Matrix 2 ->" << endl;
    print_matrix(matrix_2);
}

// Overloaded + operator for matrix addition
Matrix operator+(const Matrix& matrix_1, const Matrix& matrix_2) {
    if (matrix_1.matrix_size != matrix_2.matrix_size) {
        cerr << "Error: Matrix sizes do not match for addition." << endl;
        return Matrix();
    }
    Matrix result(matrix_1.matrix_size);
    for (int i = 0; i < matrix_1.matrix_size; ++i) {
        for (int j = 0; j < matrix_1.matrix_size; ++j) {
            result.matrix_data[i][j] = matrix_1.matrix_data[i][j] + matrix_2.matrix_data[i][j];
        }
    }
    return result;
}

// Overloaded * operator for matrix multiplication
Matrix operator*(const Matrix& matrix_1, const Matrix& matrix_2) {
    if (matrix_1.matrix_size != matrix_2.matrix_size) {
        cerr << "Error: Matrix sizes do not match for multiplication." << endl;
        return Matrix();
    }
    Matrix result(matrix_1.matrix_size);
    for (int i = 0; i < matrix_1.matrix_size; ++i) {
        for (int j = 0; j < matrix_1.matrix_size; ++j) {
            result.matrix_data[i][j] = 0;
            for (int k = 0; k < matrix_1.matrix_size; ++k) {
                result.matrix_data[i][j] += matrix_1.matrix_data[i][k] * matrix_2.matrix_data[k][j];
            }
        }
    }
    return result;
}

// Function to get the sum of the diagonal elements
void get_diagonal_sum(const Matrix& matrix) {
    double main_diagonal_sum = 0, secondary_diagonal_sum = 0;
    for (int i = 0; i < matrix.matrix_size; ++i) {
        main_diagonal_sum += matrix.matrix_data[i][i];
        secondary_diagonal_sum += matrix.matrix_data[i][matrix.matrix_size - i - 1];
    }
    cout << "Main Diagonal Sum: " << main_diagonal_sum << endl;
    cout << "Secondary Diagonal Sum: " << secondary_diagonal_sum << endl;
}

// Function to swap two rows in a specified matrix
void swap_matrix_row(Matrix& matrix) {
    int row1, row2;

    cout << "Enter the first row index to swap (0 to " << matrix.matrix_size - 1 << "): ";
    cin >> row1;
    while (row1 < 0 || row1 >= matrix.matrix_size) {
        cout << "Invalid row index. Please enter a row index between 0 and " << matrix.matrix_size - 1 << ": ";
        cin >> row1;
    }

    cout << "Enter the second row index to swap (0 to " << matrix.matrix_size - 1 << "): ";
    cin >> row2;
    while (row2 < 0 || row2 >= matrix.matrix_size) {
        cout << "Invalid row index. Please enter a row index between 0 and " << matrix.matrix_size - 1 << ": ";
        cin >> row2;
    }

    for (int i = 0; i < matrix.matrix_size; ++i) {
        std::swap(matrix.matrix_data[row1][i], matrix.matrix_data[row2][i]);
    }

    cout << "Rows " << row1 << " and " << row2 << " have been swapped." << endl;
}

int main() {
    Matrix matrix_1, matrix_2;
    read_matrix_from_file("matrix.txt", matrix_1, matrix_2);

    cout << "Printing matrices 1 and 2 below ->" << endl;
    print_matrix(matrix_1, matrix_2);

    cout << "Result of Matrix1 + Matrix2 ->" << endl;
    Matrix add_result_1 = matrix_1 + matrix_2;
    print_matrix(add_result_1);

    cout << "Result of Matrix1 * Matrix2 ->" << endl;
    Matrix multiply_result_1 = matrix_1 * matrix_2;
    print_matrix(multiply_result_1);

    cout << "Result of Sum of diagonal of a matrix ->" << endl;
    get_diagonal_sum(matrix_1);

    // Prompt user to choose between matrix_1 and matrix_2 for row swapping
    int matrix_choice;
    cout << "Enter 1 to swap rows in Matrix 1, or 2 to swap rows in Matrix 2: ";
    cin >> matrix_choice;

    while (matrix_choice != 1 && matrix_choice != 2) {
        cout << "Invalid choice. Please enter 1 for Matrix 1 or 2 for Matrix 2: ";
        cin >> matrix_choice;
    }

    if (matrix_choice == 1) {
        cout << "Swapping rows in Matrix 1 ->" << endl;
        swap_matrix_row(matrix_1);
        print_matrix(matrix_1);
        
    } else {
        cout << "Swapping rows in Matrix 2 ->" << endl;
        swap_matrix_row(matrix_2);
        print_matrix(matrix_2);
    }

   

    return 0;
}
