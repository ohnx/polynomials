#ifndef _POLY_BASIC_MATH_H_INC
#define _POLY_BASIC_MATH_H_INC
#include "polynomial.h"
#include "logger.h"
#include "math.h"

polynomial polynomial_subtract(const polynomial a, const polynomial b);
long double polynomial_calc(const polynomial a, long double x);

#endif