#include <iostream>
#include <cmath>
#include <cassert>
#include "../package/src/calculator.hpp"
using namespace std;


void assertEqual(const string& name, double result, double expected) {
    if (fabs(result - expected) > 1e-6) {
        cerr << "Test FAILED: " << name 
             << " (expected " << expected << ", got " << result << ")\n";
        assert(false);
    }
}

int main() 
{
    Calculator calc;

   
    double a, b;

  
    a = 3;  b = 4;
    assertEqual("add", calc.add(&a, &b), 7);

    a = 10; b = 4;
    assertEqual("subtract", calc.subtract(&a, &b), 6);

    a = 2;  b = 5;
    assertEqual("multiply", calc.multiply(&a, &b), 10);

    a = 10; b = 2;
    assertEqual("divide", calc.divide(&a, &b), 5);

    a = 2;  b = 3;
    assertEqual("power", calc.power(&a, &b), 8);

    a = 30;
    assertEqual("sin_deg", calc.sin_deg(&a), 0.5);

    a = 60;
    assertEqual("cos_deg", calc.cos_deg(&a), 0.5);

    a = 45;
    assertEqual("tan_deg", calc.tan_deg(&a), 1);

    a = 16;
    assertEqual("square_root", calc.square_root(&a), 4);

    a = 2.7182818;
    assertEqual("logarithm", calc.logarithm(&a), 1);


    // --- Exception Tests ---
    a = 5; b = 0;
    try { calc.divide(&a, &b); }
    catch (...) {  }
    assert( "divide(5,0) should throw");

    // sqrt(-1)
    a = -1;
    try { calc.square_root(&a); }
    catch (...) { }
    assert( "square_root(-1) should throw");

    a = -1;
    try { calc.logarithm(&a); }
    catch (...) {}
    assert("logarithm(-1) should throw");

    cout << "All tests passed successfully!"<<endl;
    return 0;
}