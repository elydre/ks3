#ifndef KS3_H
#define KS3_H

#define KS3_VERSION "0.0.2"

typedef struct {
    char *token;
    int line;
    int column;
} ks3_token_t;

typedef struct {
    ks3_token_t **tokens;
    int token_count;
} ks3_tokens_t;

// adds.c
void adds_fatal(char *format, ...);
void adds_index_to_lac(char *buf, int index, int *line, int *column);

// lexer.c
ks3_tokens_t *tokenize(char *buf);
void print_tokens(ks3_tokens_t *ks3_tokens);
void free_tokens(ks3_tokens_t *ks3_tokens);

#endif
