#include "calculator.hpp"
#include <cmath>
#include <stdexcept>

using namespace std;


double Calculator::add(const double* a, const double* b) {
    return (*a) + (*b);
}

double Calculator::subtract(const double* a, const double* b) {
    return (*a) - (*b);
}

double Calculator::multiply(const double* a, const double* b) {
    return (*a) * (*b);
}

double Calculator::divide(const double* a, const double* b) {
    if (*b == 0) throw std::runtime_error("Division by zero!");
    return (*a) / (*b);
}
double Calculator::power(const double* base, const double* exponent) {
    return std::pow(*base, *exponent);
}

double Calculator::sin_deg(const double* degrees) {
    return std::sin((*degrees) * M_PI / 180.0);
}

double Calculator::cos_deg(const double* degrees) {
    return std::cos((*degrees) * M_PI / 180.0);
}

double Calculator::tan_deg(const double* degrees) {
    return std::tan((*degrees) * M_PI / 180.0);
}

double Calculator::square_root(const double* value) {
    if (*value < 0) throw std::runtime_error("Cannot take sqrt of negative number!");
    return std::sqrt(*value);
}

double Calculator::logarithm(const double* value) {
    if (*value <= 0) throw std::runtime_error("Log undefined for <= 0!");
    return std::log(*value);
}


#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>

extern "C" {

EMSCRIPTEN_KEEPALIVE
double add(double a, double b) { return Calculator().add(a, b); }

EMSCRIPTEN_KEEPALIVE
double subtract(double a, double b) { return Calculator().subtract(a, b); }

EMSCRIPTEN_KEEPALIVE
double multiply(double a, double b) { return Calculator().multiply(a, b); }

EMSCRIPTEN_KEEPALIVE
double divide(double a, double b) { return Calculator().divide(a, b); }

EMSCRIPTEN_KEEPALIVE
double power(double a, double b) { return Calculator().power(a, b); }

EMSCRIPTEN_KEEPALIVE
double sin_deg(double v) { return Calculator().sin_deg(v); }

EMSCRIPTEN_KEEPALIVE
double cos_deg(double v) { return Calculator().cos_deg(v); }

EMSCRIPTEN_KEEPALIVE
double tan_deg(double v) { return Calculator().tan_deg(v); }

EMSCRIPTEN_KEEPALIVE
double square_root(double v) { return Calculator().square_root(v); }

EMSCRIPTEN_KEEPALIVE
double logarithm(double v) { return Calculator().logarithm(v); }

}
#endif
