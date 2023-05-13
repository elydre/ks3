#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

void adds_fatal(char *format, ...) {
    va_list args;
    va_start(args, format);
    printf("fatal error: ");
    vprintf(format, args);
    printf("\n");
    va_end(args);
    exit(1);
}
