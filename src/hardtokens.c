#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token.h"
#include "hardtokens.h"

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