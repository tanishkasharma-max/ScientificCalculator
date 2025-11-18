#include <vector>
#include <stdexcept>
#include "calculator.hpp"

using namespace std;    

class Matrix {
private:
    vector<vector<double>> matrix;
    int rows, cols;
    Calculator calc;

public:
    Matrix(int r, int c);
    Matrix(const vector<vector<double>>& mat);

    int rowCount() const { return rows; }
    int colCount() const { return cols; }
    const vector<vector<double>>& getMatrix() const 
    { 
        return matrix; 
    }

    Matrix add(const Matrix& mat) const;
    Matrix subtract(const Matrix& mat) const;
    Matrix multiply(const Matrix& mat) const;
};