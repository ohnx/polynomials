#include <stdio.h>
#include <string.h>
#include "parser.h"

int main() {
    static char str[256];
    int numRead;
    polynomial myP;
    
    while (*str != '=') {
        printf("Equation (enter '=' to quit): ");
        fgets(str, 255, stdin);
        numRead = strlen(str);
        str[numRead-1] = '\0';
        //polynomial myP = polynomial_parse("-2z^2+z^3+2z + 2 -312z^4");
        myP = polynomial_parse(str);
        printf("Degree: %d\n", myP->degree);
        polynomial_print(myP, &printf);
        free(myP);
    }
    return 0;
}