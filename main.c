#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TYPE_COUNT 3
#define INITIAL_CAPACITY 10

typedef enum { OPERAND, OPERATOR, END } Type;

typedef struct {
    Type type;
    union {
        double num;
        char op;
    } value;
} Token;

Token *tokenise(char *str);

int main(int argc, char *argv[]) {
    char test[30] = "3+ 43.67 -(6/2.5) * 2.2";
    Token *token = tokenise(test);
    printf("%s\n", test);
    if (token == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; token[i].type != END; i++) {
        if (token[i].type == OPERAND) {
            printf("Operand: %lf\n", token[i].value.num);
        } else if (token[i].type == OPERATOR) {
            printf("Operator: %c\n", token[i].value.op);
        }
    }

    free(token);
    return EXIT_SUCCESS;
}

Token *tokenise(char *str) {
    Token *token = (Token *)malloc(INITIAL_CAPACITY * sizeof(Token));
    int token_count = 0;
    int max_length = INITIAL_CAPACITY;
    if (token == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= strlen(str); i++) {
        if (token_count == max_length) {
            max_length *= 2;
            Token *tmp_token = (Token *)realloc(token, max_length * sizeof(Token));
            if (tmp_token == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                exit(EXIT_FAILURE);
            }
            token = tmp_token;
        }
        if ((isdigit(str[i])) || (str[i] == '.' && isdigit(str[i + 1]))) {
            char *endptr = NULL;
            token[token_count].type = OPERAND;
            token[token_count++].value.num = strtod(str + i, &endptr);
            i = endptr - str - 1;
        } else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '(' || str[i] == ')') {
            token[token_count].type = OPERATOR;
            token[token_count++].value.op = str[i];
        } else if (isspace(str[i])) {
            continue;
        } else if (str[i] == '\0') {
            token[token_count++].type = END;
            break;
        } else {
            fprintf(stderr, "Unexpected character '%c' in input\n", str[i]);
            free(token);
            exit(EXIT_FAILURE);
        }
    }

    return token;
}
