#ifndef _POLYNOMIAL_H_INC
#define _POLYNOMIAL_H_INC
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct _polynomial_component {
    unsigned int degree;
    double coefficient;
} polynomial_component;

typedef struct _polynomial_nonptr {
    int degree;
    polynomial_component values[0];
} polynomial_nonptr;

typedef polynomial_nonptr* polynomial;

polynomial polynomial_new(const unsigned int degree);
void polynomial_addTerm(polynomial *p_in, const polynomial_component t);

typedef int (*print_func)(const char *, ...);
void polynomial_print(const polynomial in, print_func pf);
#endif