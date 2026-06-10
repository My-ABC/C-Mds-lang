// Gen by my-peg/gen_token.py

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token.h"
#include "hardtokens.h"

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
    if (strncmp(input + *pos, "//", 2) == 0) {
        TokenInfo *token = malloc(sizeof(TokenInfo));
        if (token == NULL) {
            return NULL;
        }
        token->type = TOKEN_TDIV;
        token->text = strndup(input + *pos, 2);
        token->start_pos = *pos;
        token->end_pos = *pos + 2;
        *pos += 2;
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
    if (input[*pos] == '%') {
        TokenInfo *token = malloc(sizeof(TokenInfo));
        if (token == NULL) {
            return NULL;
        }
        token->type = TOKEN_MOD;
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
    TokenInfo *token = get_token_NUMBER(input, pos);
    if (token != NULL) {
        return token;
    }
    return NULL;
}
void free_token(TokenInfo *token) {
    if (token == NULL) return;
    if (token->text) free(token->text);
    free(token);
}
