#include "matrix.hpp"

using namespace std;


Matrix::Matrix(int r, int c)
    : rows(r), cols(c), matrix(r, vector<double>(c, 0.0)) {}


Matrix::Matrix(const std::vector<std::vector<double>>& d)
    : matrix(d), rows(d.size()), cols(d[0].size()) {}



// For Addition
Matrix Matrix::add(const Matrix& mat) const {
    if (rows != mat.rows || cols != mat.cols)
        throw runtime_error("Matrix dimension mismatch for addition!");

    Matrix result(rows, cols);    //constructur call

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.matrix[i][j] = calc.add(matrix[i][j], mat.matrix[i][j]);
        }
    }

    return result;
}

// For Subtraction
Matrix Matrix::subtract(const Matrix& mat) const {
    if (rows != mat.rows || cols != mat.cols)
        throw runtime_error("Matrix dimension mismatch for addition!");

    Matrix result(rows, cols);    //constructur call

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result.matrix[i][j] = calc.subtract(matrix[i][j], mat.matrix[i][j]);
        }
    }

    return result;
}



