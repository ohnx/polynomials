#include "pbm.h"

polynomial polynomial_subtract(const polynomial a, const polynomial b) {
    int largerDegree = a->degree > b->degree ? a->degree : b->degree;
    int i;
    polynomial p = polynomial_new(largerDegree);
    
    for (i = 0; i <= largerDegree; i++) {
        if (i > a->degree) p->values[i].coefficient = 0.0 - b->values[i].coefficient;
        else if (i > b->degree) p->values[i].coefficient = a->values[i].coefficient;
        else p->values[i].coefficient = a->values[i].coefficient - b->values[i].coefficient;
        p->values[i].degree = i;
    }
    
    return p;
}

long double polynomial_calc(const polynomial a, long double x) {
    int i;
    long double v = 0.0;
    
    for (i = 0; i <= a->degree; i++) {
        if (a->values[i].coefficient != 0.0) {
            v += a->values[i].coefficient * pow(x, a->values[i].degree);
        }
    }
    
    return v;
}
