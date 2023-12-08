#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "ks3.h"

void ks3_show_help(void) {
    puts("Usage: ks3 [options] [file]\n"
        "Options:\n"
        "  -h, --help         show this help message and exit\n"
        "  -v, --version      show version and exit\n"
        "  -t, --tokens       show tokens\n"
        "  -a, --ast          show ast\n"
        "  -i, --interactive  run in interactive mode\n"
        "\n"
        "If no file is given, ks3 will run in interactive mode.");
}

void ks3_show_usage(void) {
    puts("Usage: ks3 [options] [file]\n"
        "Try 'ks3 --help' for more information.");
}

void ks3_show_version(void) {
    puts("ks3 "KS3_VERSION);
}

ks3_agrs_t *ks3_parse_args(int argc, char **argv) {
    ks3_agrs_t *args = malloc(sizeof(ks3_agrs_t));
    if (args == NULL) {
        return NULL;
    }

    args->filename = NULL;

    args->version = 0;
    args->usage = 0;
    args->help = 0;

    args->show_tokens = 0;
    args->show_ast = 0;

    args->shell = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
                args->help = 1;
            } else if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0) {
                args->version = 1;
            } else if (strcmp(argv[i], "--tokens") == 0 || strcmp(argv[i], "-t") == 0) {
                args->show_tokens = 1;
            } else if (strcmp(argv[i], "--ast") == 0 || strcmp(argv[i], "-a") == 0) {
                args->show_ast = 1;
            } else if (strcmp(argv[i], "--interactive") == 0 || strcmp(argv[i], "-i") == 0) {
                args->shell = 1;
            } else {
                fprintf(stderr, "unknown option \"%s\"\n", argv[i]);
                args->usage = 1;
            }
        } else {
            if (args->filename != NULL) {
                fprintf(stderr, "too many arguments \"%s\"\n", argv[i]);
                args->usage = 1;
            } else {
                args->filename = argv[i];
            }
        }
    }

    if (args->filename == NULL) {
        args->shell = 1;
    }

    return args;
}
