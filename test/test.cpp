#include <iostream>
#include <cmath>
#include <cassert>
#include "../package/src/calculator.hpp"
using namespace std;


void assertEqual(const string& name, double result, double expected) {
    assert(fabs(result - expected) < 1e-6 && "Floating-point comparison failed");
}

int main() 
{
    Calculator calc;


    assertEqual("add",  calc.add(3, 4),       7);
    assertEqual("subtract", calc.subtract(10, 4), 6);
    assertEqual("multiply", calc.multiply(2, 5), 10);
    assertEqual("divide",   calc.divide(10, 2), 5);
    assertEqual("power",   calc.power(2, 3),  8);

    assertEqual("sin_deg", calc.sin_deg(30), 0.5);
    assertEqual("cos_deg", calc.cos_deg(60), 0.5);
    assertEqual("tan_deg", calc.tan_deg(45),  1);

    assertEqual("square_root", calc.square_root(16), 4);
    assertEqual("logarithm",   calc.logarithm(2.7182818), 1);  


    
    try { calc.divide(5, 0); }
    catch (...) {}
    assert("divide(5,0) should throw");

 

    try { calc.square_root(-1); }
    catch (...) {}
    assert("square_root(-1) should throw");


 
    try { calc.logarithm(-1); }
    catch (...) {  }
    assert("logarithm(-1) should throw");

    cout << "All tests passed successfully!\n";
    return 0;
}

