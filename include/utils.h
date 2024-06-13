#ifndef UTILS_H
#define UTILS_H

typedef enum { TOKEN_NUMBER, TOKEN_OPERATOR, TOKEN_PARENTHESIS } TokenType;

typedef struct {
    TokenType type;
    union {
        double num;
        char op;
        char par;
    } value;
} Token;

Token *tokenise(char *str, int type);

#endif // !UTILS_H
