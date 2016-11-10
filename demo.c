#include <stdio.h>
#include <string.h>
#include "polynomial.h"
#include "parser.h"
#include "pbm.h"

int main() {
    static char str[256];
    int numRead;
    polynomial myPA, myPB, myPC;
    
    while (*str != '=') {
        printf("Equation 1: ");
        fgets(str, 255, stdin);
        numRead = strlen(str);
        str[numRead-1] = '\0';
        myPA = polynomial_parse(str);
        printf("Degree: %d\n", myPA->degree);
        polynomial_print(myPA, &printf);
        
        printf("Equation 2: ");
        fgets(str, 255, stdin);
        numRead = strlen(str);
        str[numRead-1] = '\0';
        myPB = polynomial_parse(str);
        printf("Degree: %d\n", myPB->degree);
        polynomial_print(myPB, &printf);
        
        printf("Difference: \n");
        myPC = polynomial_subtract(myPA, myPB);
        polynomial_print(myPC, &printf);
        
        free(myPA);
        free(myPB);
        free(myPC);
    }
    return 0;
}