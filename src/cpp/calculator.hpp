#include <cmath>
#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#define EXPORT_FUNC EMSCRIPTEN_KEEPALIVE
#else
#define EXPORT_FUNC  
#endif

class Calculator {
public:
    EXPORT_FUNC double add(double a, double b);
    EXPORT_FUNC double subtract(double a, double b);
    EXPORT_FUNC double multiply(double a, double b);
    EXPORT_FUNC double divide(double a, double b);
    EXPORT_FUNC double power(double base, double exponent);
    EXPORT_FUNC double sin_deg(double degrees);
    EXPORT_FUNC double cos_deg(double degrees);
    EXPORT_FUNC double tan_deg(double degrees);
    EXPORT_FUNC double square_root(double value);
    EXPORT_FUNC double logarithm(double value);
};

