#ifndef _LOGGER_H_INC
#define _LOGGER_H_INC
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

typedef int (*logger_func)(const char *, ...);

typedef struct _logger_nonptr {
    logger_func print_error;
    logger_func print_warning;
    logger_func print_info;
    logger_func print_debug;
    
} logger_nonptr;

typedef logger_nonptr * logger;

logger logger_new(int (*errorFunc)(const char *, ...), int (*warningFunc)(const char *, ...), int (*infoFunc)(const char *, ...), int (*debugFunc)(const char *, ...));
#endif