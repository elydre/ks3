#include <stdlib.h>
#include <stdio.h>

#include "toport.h"
#include "ks3.h"

char filename[] = "file.ks";

int execute_string(char *buf, ks3_agrs_t *args) {
    ks3_tokens_t *ks3_tokens = tokenize(buf);
    if (ks3_tokens == NULL)
        return adds_raise_error("could not tokenize");
    if (args->show_tokens) print_tokens(ks3_tokens);

    ks3_ast_t **ks3_asts = parse(ks3_tokens);
    free_tokens(ks3_tokens);
    if (ks3_asts == NULL)
        return adds_raise_error("could not parse");
    if (args->show_ast) print_asts(ks3_asts);

    free_asts(ks3_asts);
    return 0;
}

int execute_file(char *filename, ks3_agrs_t *args) {
    char *buf = tp_get_file_content(filename);
    if (buf == NULL) {
        adds_raise_error("could not read file %s", filename);
    }

    int ret = execute_string(buf, args);
    free(buf);
    return ret;
}

int execute_shell(ks3_agrs_t *args) {
    (void) args;
    printf("ks3 shell not implemented yet\n");
    return 0;
}

int main(int argc, char **argv) {
    ks3_agrs_t *args = ks3_parse_args(argc, argv);

    // show usage if there was an error parsing args
    if (args->usage) {
        ks3_show_usage();
        free(args);
        return 1;
    }

    // show help or version if requested
    if (args->help) {
        ks3_show_help();
        free(args);
        return 0;
    }

    if (args->version) {
        ks3_show_version();
        free(args);
        return 0;
    }

    // execute file and exit if it fails
    if (args->filename && execute_file(args->filename, args)) {
        free(args);
        return 1;
    }

    // execute shell
    if (args->shell) {
        execute_shell(args);
    }

    free(args);
    return 0;
}
