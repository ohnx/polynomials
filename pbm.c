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
