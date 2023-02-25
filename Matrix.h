#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

using namespace std;

//template <typename T>
template <typename T>
class Matrix {
public:
    // Constructor that creates a matrix with n rows and m columns
    // Matrix(int n, int m) : data(n, std::vector<T>(m)) {}
    Matrix(int rows, int cols):data(rows, std::vector<T>(cols)){}

    // Constructor that creates a matrix with a given initializer list
    Matrix(std::initializer_list<std::initializer_list<T>> init) {
        for (const auto& row : init) {
            data.emplace_back(row);
        }
    }

    // Accessor for an element at row i and column j
    T& operator()(int i, int j) {
        return data[i][j];
    }

    // Const accessor for an element at row i and column j
    const T& operator()(int i, int j) const {
        return data[i][j];
    }

    // Returns the number of rows in the matrix
    int rows() const {
        return data.size();
    }

    // Returns the number of columns in the matrix
    int cols() const {
        return data[0].size();
    }

private:
    std::vector<std::vector<T>> data;
};

// Output stream operator for Matrix
template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
    for (int i = 0; i < matrix.rows(); i++) {
        for (int j = 0; j < matrix.cols(); j++) {
            os << matrix(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}

using IntMatrix = Matrix<uint8_t>; // Define an alias for Matrix<int>
//using NeighborMatrix = Matrix<int, 8, 2>;

#endif