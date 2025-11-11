#include<cmath>

using namespace std;

class Calculator {

    public:
    
    double add(double a, double b) {
        return a+b;
    }
    double subtract(double a, double b) {
        return a-b;
    }
    double multiply(double a, double b) {
        return a*b;
    }
    double divide(double a, double b) {
        if(b == 0) {
            throw "Division by zero error";
        }
        return a/b;
    }
    double power(double base, double exponent) {
        return pow(base, exponent);
    } 
    double sin_deg(double degrees)
    {
        return sin(degrees * M_PI / 180.0);
    }      
    double cos_deg(double degrees)
    {
        return cos(degrees * M_PI / 180.0);
    }
    double tan_deg(double degrees)
    {
        return tan(degrees * M_PI / 180.0);
    }
    double power(double base, int exponent) {
        return std::pow(base, exponent);
    } 
    double square_root(double value) {
        if(value < 0) {
            throw "Square root of negative number error";
        }
        return sqrt(value);
    }
    double logarithm(double value) {
        if(value <= 0) {
            throw "Log of non-positive number error";
        }
        return log(value);
    }
};
extern "C" {
    double add(double a, double b) {
        Calculator c; 
        return c.add(a, b);
    }
    double subtract(double a, double b) {
        Calculator c; 
        return c.subtract(a, b);
    }
    double multiply(double a, double b) {
        Calculator c; 
        return c.multiply(a, b);
    }
    double divide(double a, double b) {
        Calculator c; 
        return c.divide(a, b);
    }
    double power(double a, double b) {
        Calculator c; 
        return c.power(a, b);
    }
    double sin_deg(double a) {
        Calculator c; 
        return c.sin_deg(a);
    }
    double cos_deg(double a) {
        Calculator c; 
        return c.cos_deg(a);
    }
    double tan_deg(double a) {
        Calculator c; 
        return c.tan_deg(a);
    }
    double square_root(double a) {
        Calculator c; 
        return c.square_root(a);
    }
    double logarithm(double a) {
        Calculator c; 
        return c.logarithm(a);
    }
}