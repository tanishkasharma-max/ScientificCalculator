#include <iostream>
#include<cassert>
#include "../package/src/matrix.hpp"
using namespace std;


void test(const std::string& name, double result, double expected) {
    assert(std::abs(result - expected) < 1e-6 && "Test failed!");
}

int main() {
    Matrix A({{1, 2}, {3, 4}});
    Matrix B({{5, 6}, {7, 8}});

    Matrix C = A.add(B);
    Matrix D = A.subtract(B);

    test("A+B [0][0]", C.getMatrix()[0][0], 6);
    test("A+B [0][1]", C.getMatrix()[0][1], 8);
    test("A+B [1][0]", C.getMatrix()[1][0], 10);
    test("A+B [1][1]", C.getMatrix()[1][1], 12);

    test("A-B [0][0]", D.getMatrix()[0][0], -4);
    test("A-B [0][1]", D.getMatrix()[0][1], -4);
    test("A-B [1][0]", D.getMatrix()[1][0], -4);
    test("A-B [1][1]", D.getMatrix()[1][1], -4);

    return 0;
}