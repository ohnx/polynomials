#include "logger.h"

int do_nothing(const char * format, ...) {
    return 0;
}

logger logger_new(logger_func errorFunc, logger_func warningFunc, logger_func infoFunc, logger_func debugFunc) {
    logger l = calloc(1, sizeof(logger));
    l->print_error = errorFunc;
    l->print_warning = warningFunc;
    l->print_info = infoFunc;
    l->print_debug = debugFunc;
    return l;
}

