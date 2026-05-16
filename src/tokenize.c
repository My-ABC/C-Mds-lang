#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token.h"
#include "hardtokens.h"

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

TokenInfo *get_next_token(const char* input, int *pos) {
    if (input[*pos] == '\0') {
        TokenInfo *token = malloc(sizeof(TokenInfo));
        if (token == NULL) {
            return NULL;
        }
        token->type = TOKEN_EOF;
        token->text = NULL;
        token->start_pos = *pos;
        token->end_pos = *pos;
        return token;
    }
    if (input[*pos] == '\n') {
        TokenInfo *token = malloc(sizeof(TokenInfo));
        if (token == NULL) {
            return NULL;
        }
        token->type = TOKEN_NL;
        token->text = NULL;
        token->start_pos = *pos;
        token->end_pos = *pos + 1;
        *pos += 1;
        return token;
    }
    if (input[*pos] == ' ') {
        *pos += 1;
        return get_next_token(input, pos);
    }
    TokenInfo *token = get_token_NUMBER(input, pos);
    if (token != NULL) {
        return token;
    }
    if (strncmp(input + *pos, "**", 2) == 0) {
        TokenInfo *token = malloc(sizeof(TokenInfo));
        if (token == NULL) {
            return NULL;
        }
        token->type = TOKEN_POWER;
        token->text = strndup(input + *pos, 2);
        token->start_pos = *pos;
        token->end_pos = *pos + 2;
        *pos += 2;
        return token;
    }
    if (input[*pos] == '+') {
        TokenInfo *token = malloc(sizeof(TokenInfo));
        if (token == NULL) {
            return NULL;
        }
        token->type = TOKEN_ADD;
        token->text = strndup(input + *pos, 1);
        token->start_pos = *pos;
        token->end_pos = *pos + 1;
        *pos += 1;
        return token;
    }
    if (input[*pos] == '-') {
        TokenInfo *token = malloc(sizeof(TokenInfo));
        if (token == NULL) {
            return NULL;
        }
        token->type = TOKEN_SUB;
        token->text = strndup(input + *pos, 1);
        token->start_pos = *pos;
        token->end_pos = *pos + 1;
        *pos += 1;
        return token;
    }
    if (input[*pos] == '*') {
        TokenInfo *token = malloc(sizeof(TokenInfo));
        if (token == NULL) {
            return NULL;
        }
        token->type = TOKEN_MUL;
        token->text = strndup(input + *pos, 1);
        token->start_pos = *pos;
        token->end_pos = *pos + 1;
        *pos += 1;
        return token;
    }
    if (input[*pos] == '/') {
        TokenInfo *token = malloc(sizeof(TokenInfo));
        if (token == NULL) {
            return NULL;
        }
        token->type = TOKEN_DIV;
        token->text = strndup(input + *pos, 1);
        token->start_pos = *pos;
        token->end_pos = *pos + 1;
        *pos += 1;
        return token;
    }
    if (input[*pos] == '(') {
        TokenInfo *token = malloc(sizeof(TokenInfo));
        if (token == NULL) {
            return NULL;
        }
        token->type = TOKEN_LP;
        token->text = strndup(input + *pos, 1);
        token->start_pos = *pos;
        token->end_pos = *pos + 1;
        *pos += 1;
        return token;
    }
    if (input[*pos] == ')') {
        TokenInfo *token = malloc(sizeof(TokenInfo));
        if (token == NULL) {
            return NULL;
        }
        token->type = TOKEN_RP;
        token->text = strndup(input + *pos, 1);
        token->start_pos = *pos;
        token->end_pos = *pos + 1;
        *pos += 1;
        return token;
    }
    return NULL;
}
