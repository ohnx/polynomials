#include "parser.h"
#include "logger.h"

polynomial polynomial_parse(const char *in) {
    const char *last, *tkStart, *tkEnd;
    char *temp;
    
    polynomial_component currPC;
    polynomial newPolynomial = NULL;
    
    char var = 0;
    double valA = 0, valB = 0;
    int fraction = 0;
    int sign;
    
    enum _PARSE_CURR {
        SIGN,
        COEFFICIENT_START,
        COEFFICIENT_END,
        VAR_START,
        EXPONENT_START,
        EXPONENT_END,
    } currSearch = SIGN;
    //char * strs[] = {"SIGN", "COEFFICIENT_START", "COEFFICIENT_END", "VAR_START", "EXPONENT_START", "EXPONENT_END"};
    
    last = in;
    last--;
    
    do {
        last++;
        //l->print_debug("looking at %c with value %s\n", *last, strs[currSearch]);
        //printf("looking at %c with value %s\n", *last, strs[currSearch]);
        switch (currSearch) {
        case SIGN:
            if (*last == '-') { /* we do have a sign */
                sign = -1;
                currSearch = COEFFICIENT_START;
            } else if (*last == '+') { /* we do have a sign */
                sign = 1;
                currSearch = COEFFICIENT_START;
            } else if (!((*last <= '9' && *last >= '0')||(*last <= 'z' && *last >= 'a')||(*last <= 'Z' && *last >= 'A'))) { /* no sign, no number, so keep going */
                
            } else {
                /* no sign, but there is a number */
                sign = 1;
                currSearch = COEFFICIENT_START;
                goto COEFFICIENT_START_case;
            }
            break;
        case COEFFICIENT_START:
        COEFFICIENT_START_case:
            if (*last <= '9' && *last >= '0') {
                tkStart = last;
                currSearch = COEFFICIENT_END;
                break;
            } else if (*last == ' ') {
                break;
            }
            
            /* we are on a letter, so we can assume that the coefficient is 1 */
            currPC.coefficient = 1*sign;
            currSearch = VAR_START;
            goto VAR_START_case;
        case COEFFICIENT_END:
            if (*last == '/') { /* we hit a fraction */
                tkEnd = last;
                temp = strndup(tkStart, tkEnd-tkStart);
                tkStart = last+1;
                sscanf(temp, "%lf", &valA);
                
                free(temp);
                fraction = 1;
                break;
            } else if ((*last < '.' || *last > '9') && *last != '\0') { /* number end */
                tkEnd = last;
                temp = strndup(tkStart, tkEnd-tkStart);

                if (fraction) { /* handle fraction */
                   sscanf(temp, "%lf", &valB);
                    if (valB == 0) {
                        //l->print_error("Diving by zero: %f/%f!", valA, valB);
                        return NULL;
                    }

                    valA = valA/valB;
                } else { /* normal handling */
                    sscanf(temp, "%lf", &valA);
                }
                
                currPC.coefficient = valA*sign; /* will be -1 or 1 already */
                currSearch = VAR_START;
                free(temp);
                
                /* reset fraction flag */
                fraction = 0;
            } else { /* is a number, keep going */
                break;
            }
            /* do not break in this case; go directly to VAR_START */
        case VAR_START:
        VAR_START_case:
            if (var == 0) { /* no var set yet, so we'll use this one */
                var = *last;
                //logger->print_info("`%c` detected as variable in polynomial", var);
                currSearch = EXPONENT_START;
            } else if (*last == var) { /* found the var */
                currSearch = EXPONENT_START;
                if (*(last+1) != '^') { /* no exponent */
                    currPC.degree = 1;
                    goto ADD_POLYNOMIAL;
                }
            } else if (*last == '+' || *last == '-') { /* no variable, it is a constant */
                currPC.degree = 0;
                last--;
                goto ADD_POLYNOMIAL;
            }
            /* no var found, keep going */
            break;
        case EXPONENT_START:
            if (*last <= '9' && *last >= '0') {
                tkStart = last;
                currSearch = EXPONENT_END;
            } else if (*last == '+' || *last == '-') { /* exponent is 1 */
                currPC.degree = 1;
                last--;
                goto ADD_POLYNOMIAL;
            }
            break;
        case EXPONENT_END:
            if (*last < '0' || *last > '9') { /* exponent ended */
                tkEnd = last;
                
                temp = strndup(tkStart, tkEnd-tkStart);
                currPC.degree = atoi(temp);
                free(temp);
                
            ADD_POLYNOMIAL:
                //printf("adding %f%c^%d to the polynomial\n", currPC.coefficient, var, currPC.degree);
                
                /* add the polynomial component to the list */
                polynomial_addTerm(&newPolynomial, currPC);
                
                currPC.degree = 0;
                currPC.coefficient = 0.0;
                valA = 0;
                
                currSearch = SIGN;
                
                if (*last == '+' || *last == '-') { /* need to go back so we can catch SIGN again*/
                    last--;
                }
            }
            break;
        }
    }  while (*last != '\0');
    
    if (currSearch != SIGN && currSearch != VAR_START && currSearch != COEFFICIENT_END
     && !(currSearch == EXPONENT_START && *last == '\0')) {
        //logger->print_error("Parsing ended unexpectedly.");
        printf("Parsing ended unexpectedly.\n");
    }
    
    /* degree 1 polynomial */
    if (currSearch == EXPONENT_START) {
        currPC.degree = 1;
        tkEnd = last;
        temp = strndup(tkStart, tkEnd-tkStart);
        
        if (valA == 0.0) sscanf(temp, "%lf", &valA);
        
        currPC.coefficient = valA*sign; /* will be -1 or 1 already */
        currSearch = VAR_START;
        free(temp);
        
        //printf("adding %fx^%d to the polynomial\n", currPC.coefficient, currPC.degree);
                
        /* add the polynomial component to the list */
        polynomial_addTerm(&newPolynomial, currPC);
    } else if (currSearch == COEFFICIENT_END || (currSearch == VAR_START)) { /* degree 0 polynomial */
        currPC.degree = 0;
        
        tkEnd = last;
        temp = strndup(tkStart, tkEnd-tkStart);
        
        if (fraction) { /* handle fraction */
           sscanf(temp, "%lf", &valB);
            if (valB == 0) {
                //l->print_error("Diving by zero: %f/%f!", valA, valB);
                return NULL;
            }

            valA = valA/valB;
        } else { /* normal handling */
            sscanf(temp, "%lf", &valA);
        }
        
        currPC.coefficient = valA*sign; /* will be -1 or 1 already */
        currSearch = VAR_START;
        free(temp);
        
        //printf("adding %fx^%d to the polynomial\n", currPC.coefficient, currPC.degree);
                
        /* add the polynomial component to the list */
        polynomial_addTerm(&newPolynomial, currPC);
    }
    
    return newPolynomial;
}

