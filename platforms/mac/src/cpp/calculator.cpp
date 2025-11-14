#include "calculator.hpp"
#include <cmath>
#include <stdexcept>

using namespace std;


double Calculator::add(double a, double b) {
    return a + b;
}

double Calculator::subtract(double a, double b) {
    return a - b;
}

double Calculator::multiply(double a, double b) {
    return a * b;
}

double Calculator::divide(double a, double b) {
    if (b == 0)
        throw runtime_error("Division by zero");
    return a / b;
}

double Calculator::power(double base, double exponent) {
    return pow(base, exponent);
}

double Calculator::sin_deg(double degrees) {
    return sin(degrees * M_PI / 180.0);
}

double Calculator::cos_deg(double degrees) {
    return cos(degrees * M_PI / 180.0);
}

double Calculator::tan_deg(double degrees) {
    return tan(degrees * M_PI / 180.0);
}

double Calculator::square_root(double value) {
    if (value < 0)
        throw runtime_error("Square root of negative number");
    return sqrt(value);
}

double Calculator::logarithm(double value) {
    if (value <= 0)
        throw runtime_error("Logarithm of negative number");
    return log(value);
}
