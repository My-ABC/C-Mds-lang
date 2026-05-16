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

TokenInfo* get_token_NUMBER(const char* input, int *pos) {
    if (isdigit(input[*pos])) {
        int start_pos = *pos;
        while (isdigit(input[*pos])) {
            *pos += 1;
        }
        TokenInfo *token = malloc(sizeof(TokenInfo));
        if (token == NULL) {
            return NULL;
        }
        token->type = TOKEN_NUMBER;
        token->text = strndup(input + start_pos, *pos - start_pos);
        token->start_pos = start_pos;
        token->end_pos = *pos;
        return token;
    }
    return NULL;
}