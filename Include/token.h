// Gen by my-peg/gen_token.py

#pragma once

#if defined(_WIN32) || defined(_WIN64)
static char* strndup(const char* s, size_t n) {
    size_t len = 0;
    const char* p = s;
    while (len < n && *p) {
        len++;
        p++;
    }
    char* result = (char*)malloc(len + 1);
    if (result) {
        memcpy(result, s, len);
        result[len] = '\0';
    }
    return result;
}

#endif

typedef enum _token {
    TOKEN_TDIV,
    TOKEN_POWER,
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_MOD,
    TOKEN_LP,
    TOKEN_RP,
    TOKEN_NUMBER,
    TOKEN_NL,
    TOKEN_EOF
} TokenType;

typedef struct _tokeninfo {
    TokenType type;
    char *text;
    int start_pos;
    int end_pos;
} TokenInfo;

TokenInfo *get_next_token(const char* input, int *pos);
void free_token(TokenInfo *token);
