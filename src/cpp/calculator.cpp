#include <iostream>
#include "calculator.hpp"

using namespace std;

int main() {
    Calculator calc;
    double a, b, angle;

    cout << "Enter two numbers: ";
    cin >> a >> b;

    cout << "Addition: " << calc.add(a, b) << endl;
    cout << "Subtraction: " << calc.subtract(a, b) << endl;
    cout << "Multiplication: " << calc.multiply(a, b) << endl;
    cout << "Division: " << calc.divide(a, b) << endl;

    cout << "Enter an angle in degrees: ";
    cin >> angle;

    cout << "Sine(" << angle << "°): " << calc.sin_deg(angle) << endl;
    cout << "Cosine(" << angle << "°): " << calc.cos_deg(angle) << endl;
    cout << "Tangent(" << angle << "°): " << calc.tan_deg(angle) << endl;

    return 0;
}
