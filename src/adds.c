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

void adds_index_to_lac(char *buf, int index, int *line, int *column) {
    *line = 1;
    *column = 1;
    for (int i = 0; i < index; i++) {
        if (buf[i] == '\n') {
            (*line)++;
            *column = 1;
        } else {
            (*column)++;
        }
    }
}
