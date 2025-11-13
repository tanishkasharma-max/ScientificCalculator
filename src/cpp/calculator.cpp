#include "calculator.hpp"
using namespace std;

double Calculator::add(double a, double b) 
             { return a + b; }
double Calculator::subtract(double a, double b) 
             { return a - b; }
double Calculator::multiply(double a, double b) 
             { return a * b; }
double Calculator::divide(double a, double b) 
            { return b != 0 ? a / b : 0; }
double Calculator::power(double base, double exponent) 
            { return pow(base, exponent); }
double Calculator::sin_deg(double degrees) 
            { return sin(degrees * M_PI / 180.0); }
double Calculator::cos_deg(double degrees) 
           { return cos(degrees * M_PI / 180.0); }
double Calculator::tan_deg(double degrees) 
          { return std::tan(degrees * M_PI / 180.0); }
double Calculator::square_root(double value) 
          { return value >= 0 ? sqrt(value) : 0; }
double Calculator::logarithm(double value) 
          { return value > 0 ? log(value) : 0; }
