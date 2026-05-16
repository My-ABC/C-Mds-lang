typedef enum _token {
    TOKEN_NUMBER,
    TOKEN_POWER,
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_LP,
    TOKEN_RP,
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
