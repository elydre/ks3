#ifndef KS3_H
#define KS3_H

#define KS3_VERSION "0.0.3"

typedef enum {
    TYPE_INTEGER,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_BOOLEAN,
    TYPE_ARRAY,

    TYPE_OPERATOR,
    TYPE_KEYWORD,

    TYPE_FUNCTION_CALL,
    TYPE_FUNCTION_DEF,

    TYPE_VARIABLE_SET,
    TYPE_VARIABLE_GET,

    TYPE_NULL,
} ks3_type_t;

typedef enum {
    OP_ADD, // +
    OP_SUB, // -
    OP_MUL, // *
    OP_DIV, // /
    OP_MOD, // %

    OP_AND, // &&
    OP_OR,  // ||
    OP_NOT, // !

    OP_EQ,  // ==
    OP_NE,  // !=
    OP_GT,  // =+=
    OP_LT,  // =-=

    OP_NULL,
} ks3_operator_t;

typedef enum {
    KEYWORD_IF,
    KEYWORD_ELSE,
    KEYWORD_ELIF,
    KEYWORD_WHILE,
    KEYWORD_DEF,
    KEYWORD_RETURN,
    KEYWORD_NIL,
    KEYWORD_BREAK,
} ks3_keyword_t;

// token_t
typedef struct {
    char *token;
    int line;
    int column;
} ks3_token_t;

// tokens_t
typedef struct {
    ks3_token_t **tokens;
    int token_count;
} ks3_tokens_t;

// obj_t
typedef struct {
    char *name;         // can be NULL
    ks3_type_t type;
    ks3_operator_t op;  // can be NULL
    ks3_keyword_t kw;   // can be NULL
    void *cnt;          // can be NULL

    int int_val;        // for TYPE_INTEGER
    float float_val;    // for TYPE_FLOAT

    ks3_token_t *token;
} ks3_obj_t;

// ast_t
typedef struct {
    ks3_obj_t **objs;
    int obj_count;
} ks3_ast_t;

// adds.c
void adds_fatal(char *format, ...);
void adds_index_to_lac(char *buf, int index, int *line, int *column);

// lexer.c
ks3_tokens_t *tokenize(char *buf);
void print_tokens(ks3_tokens_t *ks3_tokens);
void free_tokens(ks3_tokens_t *ks3_tokens);

// parser.c
ks3_ast_t *parse(ks3_tokens_t *ks3_tokens);

#endif
