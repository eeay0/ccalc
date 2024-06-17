typedef enum { num, op, par } Type;

typedef struct {
    Type type;
    union {
        double num;
        char op;
        char par;
    } value;
} Token;

int check_type(char ch);
int assign_value(char *str, Token *token);
Token *tokenise(char *str);
void parse(Token *t);
