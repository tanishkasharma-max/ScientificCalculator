#include <cmath>


class Calculator {
public:
    static double add(const double* a, const double* b);
    static double subtract(const double* a, const double* b);
    static double multiply(const double* a, const double* b);
    static double divide(const double* a, const double* b);
    static double power(const double* base, const double* exponent);
    static double sin_deg(const double* degrees);
    static double cos_deg(const double* degrees);
    static double tan_deg(const double* degrees);
    static double square_root(const double* value);
    static double logarithm(const double* value);
};

