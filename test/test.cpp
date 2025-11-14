#include <iostream>
#include <cmath>
#include "../platforms/mac/src/cpp/calculator.hpp"
using namespace std;

void test(const string& name, double result, double expected) {
    if (abs(result - expected) < 1e-6) {
        cout << name << ": PASS"<<endl;
    } else {
        cout << name << ": FAIL"<<endl;
    }
}

int main() 
{
    Calculator calc;

   
    test("add(3,4)", calc.add(3, 4), 7);
    test("subtract(10,4)", calc.subtract(10, 4), 6);
    test("multiply(2,5)", calc.multiply(2, 5), 10);
    test("divide(10,2)", calc.divide(10, 2), 5);
    test("power(2,3)", calc.power(2, 3), 8);


    test("sin_deg(30)", calc.sin_deg(30), 0.5);
    test("cos_deg(60)", calc.cos_deg(60), 0.5);
    test("tan_deg(45)", calc.tan_deg(45), 1);

    test("square_root(16)", calc.square_root(16), 4);
    test("logarithm(e)", calc.logarithm(2.7), 1); 

    try {
        calc.divide(5, 0);
        std::cout << "divide(5,0): FAIL (no exception)"<<endl;
    } catch (...) {
        std::cout << "divide(5,0): PASS (caught exception)\n";
    }

    try {
        calc.square_root(-1);
        std::cout << "square_root(-1): FAIL no exception"<<endl;
    } catch (...) {
        std::cout << "square_root(-1): PASS caught exception"<<endl;
    }

    try {
        calc.logarithm(-1);
        std::cout << "logarithm(-1): FAIL no exception"<<endl;
    } catch (...) {
        std::cout << "logarithm(-1): PASS caught exception"<<endl;
    }

    return 0;
}
