#ifndef _PARSER_H_INC
#define _PARSER_H_INC
#include <stdlib.h>
#include <string.h>
#include "polynomial.h"
#include "logger.h"
#include <stdio.h>

polynomial polynomial_parse(const char *in);

#define _okhere() do { printf("ok %d\n", __LINE__); fflush(stdout); } while(0)
#endif