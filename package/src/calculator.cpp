#include "calculator.hpp"
#include <stdexcept>
#include <cmath>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#include <cstddef>

// Optional memory tracking
size_t totalAllocated = 0;
void* operator new(size_t size) {
    totalAllocated += size;
    return malloc(size);
}
void operator delete(void* ptr, size_t size) noexcept {
    totalAllocated -= size;
    free(ptr);
}
#endif

using namespace std;

double* Calculator::add(const double* a, const double* b) {
    return new double(*a + *b);
}

double* Calculator::subtract(const double* a, const double* b) {
    return new double(*a - *b);
}

double* Calculator::multiply(const double* a, const double* b) {
    return new double(*a * *b);
}

double* Calculator::divide(const double* a, const double* b) {
    if (*b == 0) throw runtime_error("Division by zero!");
    return new double(*a / *b);
}

double* Calculator::power(const double* base, const double* exponent) {
    return new double(pow(*base, *exponent));
}

double* Calculator::sin_deg(const double* degrees) {
    return new double(sin(*degrees * M_PI / 180.0));
}

double* Calculator::cos_deg(const double* degrees) {
    return new double(cos(*degrees * M_PI / 180.0));
}

double* Calculator::tan_deg(const double* degrees) {
    return new double(tan(*degrees * M_PI / 180.0));
}

double* Calculator::square_root(const double* value) {
    if (*value < 0) throw runtime_error("Cannot take sqrt of negative number!");
    return new double(sqrt(*value));
}

double* Calculator::logarithm(const double* value) {
    if (*value <= 0) throw runtime_error("Log undefined for <= 0!");
    return new double(log(*value));
}

#ifdef __EMSCRIPTEN__
extern "C" {

// EMSCRIPTEN wrappers: return by value, safe for JS
EMSCRIPTEN_KEEPALIVE double add(double a, double b) {
    double* result = Calculator::add(&a, &b);
    double val = *result;
    delete result;
    return val;
}

EMSCRIPTEN_KEEPALIVE double subtract(double a, double b) {
    double* result = Calculator::subtract(&a, &b);
    double val = *result;
    delete result;
    return val;
}

EMSCRIPTEN_KEEPALIVE double multiply(double a, double b) {
    double* result = Calculator::multiply(&a, &b);
    double val = *result;
    delete result;
    return val;
}

EMSCRIPTEN_KEEPALIVE double divide(double a, double b) {
    double* result = Calculator::divide(&a, &b);
    double val = *result;
    delete result;
    return val;
}

EMSCRIPTEN_KEEPALIVE double power(double a, double b) {
    double* result = Calculator::power(&a, &b);
    double val = *result;
    delete result;
    return val;
}

EMSCRIPTEN_KEEPALIVE double sin_deg(double v) {
    double* result = Calculator::sin_deg(&v);
    double val = *result;
    delete result;
    return val;
}

EMSCRIPTEN_KEEPALIVE double cos_deg(double v) {
    double* result = Calculator::cos_deg(&v);
    double val = *result;
    delete result;
    return val;
}

EMSCRIPTEN_KEEPALIVE double tan_deg(double v) {
    double* result = Calculator::tan_deg(&v);
    double val = *result;
    delete result;
    return val;
}

EMSCRIPTEN_KEEPALIVE double square_root(double v) {
    double* result = Calculator::square_root(&v);
    double val = *result;
    delete result;
    return val;
}

EMSCRIPTEN_KEEPALIVE double logarithm(double v) {
    double* result = Calculator::logarithm(&v);
    double val = *result;
    delete result;
    return val;
}

EMSCRIPTEN_KEEPALIVE size_t getMemoryUsage() { return totalAllocated; }

}
#endif
