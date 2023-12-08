#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

int adds_raise_error(char *format, ...) {
    va_list args;
    va_start(args, format);
    fputs("KS3 Error: ", stderr);
    vfprintf(stderr, format, args);
    fputc('\n', stderr);
    va_end(args);
    return 1;
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
