#include "polynomial.h"

/*void hexDump (char *desc, void *addr, int len) {
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;

    // Output description if given.
    if (desc != NULL)
        printf ("%s:\n", desc);

    if (len == 0) {
        printf("  ZERO LENGTH\n");
        return;
    }
    if (len < 0) {
        printf("  NEGATIVE LENGTH: %i\n",len);
        return;
    }

    // Process every byte in the data.
    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0)
                printf ("  %s\n", buff);

            // Output the offset.
            printf ("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf (" %02x", pc[i]);

        // And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e))
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        printf ("   ");
        i++;
    }

    // And print the final ASCII bit.
    printf ("  %s\n", buff);
}*/

polynomial polynomial_new(const unsigned int degree) {
    polynomial p = calloc(1, sizeof(polynomial)+sizeof(polynomial_component)*(degree+1));
    p->degree = degree;
    return p;
}

void polynomial_addTerm(polynomial *p_in, const polynomial_component t) {
    polynomial p = *p_in;
    polynomial n;
    
    if (p == NULL) { /* need to alloc since new polynomial */
        p = polynomial_new(t.degree);
    } else if (p->degree < t.degree) { /* need to alloc since the adding degree is more */
        /* reallocate memory to the new size */
        n = calloc(1, sizeof(polynomial)+sizeof(polynomial_component)*(t.degree+1));
        
        /* copy over the things with a certain offset */
        //hexDump("original", p->values, sizeof(polynomial_component)*(p->degree+1));
        memcpy(&n->values, p->values, sizeof(polynomial_component)*(p->degree+1));
        //hexDump("new", n->values, sizeof(polynomial_component)*(t.degree+1));
        n->degree = t.degree;
        
        free(p);
        p = n;
    }
    
    /* copy t's values over */
    memcpy(&p->values[t.degree], &t, sizeof(polynomial_component));
    
    *p_in = p;
}

void polynomial_print(const polynomial in, print_func pf) {
    int i;
    polynomial_component *pc = in->values+in->degree;
    for (i = 0; i <= in->degree; i++) {
        if (pc->coefficient != 0.0) {
            printf(" %fx^%d ", pc->coefficient, pc->degree);
        }
        pc--;
    }
    printf("\n");
}