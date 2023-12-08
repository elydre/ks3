#include <stdlib.h>
#include <stdio.h>

#include "toport.h"
#include "ks3.h"

/* read file contents into a buffer, return
 * new buffer if successful else NULL */

char *tp_get_file_content(char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) return NULL;

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buf = malloc(fsize + 1);
    fread(buf, fsize, 1, f);
    fclose(f);

    buf[fsize] = 0;
    return buf;
}
