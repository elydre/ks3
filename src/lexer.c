#define TOKEN_INCREMENT 10

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "ks3.h"

char cutat[] = "\"'+-*/&|^~<>=!?:;,.(){}[]";

ks3_token_t **add_to_tokens(int token_count, ks3_token_t **tokens, char *token, int line, int column) {
    // printf("adding token: %s\n", token);
    if (token_count % TOKEN_INCREMENT == 0) {
        tokens = realloc(tokens, sizeof(ks3_token_t *) * (token_count + TOKEN_INCREMENT));
    }

    tokens[token_count] = malloc(sizeof(ks3_token_t));
    tokens[token_count]->token = token;
    tokens[token_count]->line = line;
    tokens[token_count]->column = column;
    return tokens;
}

void print_tokens(ks3_tokens_t *ks3_tokens) {
    for (int i = 0; i < ks3_tokens->token_count; i++) {
        printf("[%s, l%d, c%d]\n",
                ks3_tokens->tokens[i]->token,
                ks3_tokens->tokens[i]->line,
                ks3_tokens->tokens[i]->column
        );
    }
}

void free_tokens(ks3_tokens_t *ks3_tokens) {
    for (int i = 0; i < ks3_tokens->token_count; i++) {
        free(ks3_tokens->tokens[i]->token);
        free(ks3_tokens->tokens[i]);
    }
    free(ks3_tokens->tokens);
    free(ks3_tokens);
}

void add_if_nessary(int *token_count, ks3_token_t **tokens, int index, int token_start, char *buf) {
    if (index - token_start > 0) {
        char *token = malloc(index - token_start + 1);
        memcpy(token, buf + token_start, index - token_start);
        token[index - token_start] = '\0';
        int line, column;
        adds_index_to_lac(buf, token_start, &line, &column);
        tokens = add_to_tokens(*token_count, tokens, token, line, column);
        (*token_count)++;
    }
}

ks3_tokens_t *tokenize(char *buf) {
    int token_count = 0;
    ks3_token_t **tokens = malloc(sizeof(ks3_token_t *) * TOKEN_INCREMENT);

    int index = 0;
    int token_start = 0;

    int line, column;

    while (buf[index] != '\0') {
        // comment
        if (buf[index] == '/' && buf[index + 1] == '/') {
            while (buf[index] != '\n' && buf[index] != '\0') {
                index++;
            }
            while (buf[index] == ' ' || buf[index] == '\n' || buf[index] == '\t') {
                index++;
            }
            token_start = index;
        }

        // multiline comment
        else if (buf[index] == '/' && buf[index + 1] == '*') {
            while (buf[index] != '\0') {
                if (buf[index] == '*' && buf[index + 1] == '/') {
                    index += 2;
                    break;
                }
                index++;
            }
            while (buf[index] == ' ' || buf[index] == '\n' || buf[index] == '\t') {
                index++;
            }
            token_start = index;
        }

        // space or newline
        else if (buf[index] == ' ' || buf[index] == '\n') {
            add_if_nessary(&token_count, tokens, index, token_start, buf);
            while (buf[index] == ' ' || buf[index] == '\n' || buf[index] == '\t') {
                index++;
            }
            token_start = index;
        }

        // cutat
        else if (strchr(cutat, buf[index]) != NULL) {
            add_if_nessary(&token_count, tokens, index, token_start, buf);
            char *token = malloc(2);
            token[0] = buf[index];
            token[1] = '\0';
            adds_index_to_lac(buf, index, &line, &column);
            tokens = add_to_tokens(token_count, tokens, token, line, column);
            token_count++;
            index++;
            token_start = index;
        }

        else index++;
    }

    add_if_nessary(&token_count, tokens, index, token_start, buf);

    tokens = add_to_tokens(token_count, tokens, NULL, 0, 0);

    ks3_tokens_t *ks3_tokens = malloc(sizeof(ks3_tokens_t));
    ks3_tokens->tokens = tokens;
    ks3_tokens->token_count = token_count;

    return ks3_tokens;
}
