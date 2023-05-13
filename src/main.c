#include <stdlib.h>
#include <stdio.h>

#include "toport.h"
#include "ks3.h"

char filename[] = "file.ks";

int main(int argc, char **argv) {
    (void) argc;
    (void) argv;

    char *buf = tp_get_file_content(filename);
    if (buf == NULL) {
        adds_fatal("could not read file %s", filename);
    }

    ks3_tokens_t *ks3_tokens = tokenize(buf);
    print_tokens(ks3_tokens);

    free_tokens(ks3_tokens);
    free(buf);
}
