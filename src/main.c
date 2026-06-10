#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "token.h"

#define DEBUG 1
#ifndef NDEBUG
    #define D(x) do { if (DEBUG) { x; } } while (0)
#else
    #define D(x)
#endif

int main() {
    char *inp = "1 + 1";
    TokenInfo *tokens;
    int *pos = malloc(sizeof(int));
    if (pos == NULL) {
        return -1;
    }
    *pos = 0;

    while (1) {
        tokens = get_next_token(inp, pos);
        if (tokens == NULL) {
            break;
        }
        if (tokens->type == TOKEN_EOF) {
            free_token(tokens);
            break;
        }
        
        printf("Token: type=%d, text='%s', start_pos=%d, end_pos=%d\n",
               tokens->type, tokens->text, tokens->start_pos, tokens->end_pos);
    
        free_token(tokens);
    }

    tokens = NULL;
    free(pos);
    

    return 0;
}