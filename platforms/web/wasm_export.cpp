#ifdef __EMSCRIPTEN__
#include "calculator.hpp"
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
double sin_deg(double a) { return Calculator().sin_deg(a); }

EMSCRIPTEN_KEEPALIVE
double cos_deg(double a) { return Calculator().cos_deg(a); }

EMSCRIPTEN_KEEPALIVE
double tan_deg(double a) { return Calculator().tan_deg(a); }

EMSCRIPTEN_KEEPALIVE
double square_root(double v) { return Calculator().square_root(v); }

EMSCRIPTEN_KEEPALIVE
double logarithm(double v) { return Calculator().logarithm(v); }

}
#endif
