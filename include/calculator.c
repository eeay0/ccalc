#include "../header/global_vars.h"
#include "../header/stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char delimiters[TYPE_COUNT][11] = {"0123456789", "+-*/", "()"};
int token_count;

int check_type(char ch) {
    for (int i = 0; i < TYPE_COUNT; i++) {
        for (int y = 0; delimiters[i][y] != '\0'; y++) {
            if (delimiters[i][y] == ch) {
                return i;
            }
        }
    }
    return -1;
}

int assign_value(char *str, Token *token) {
    if (token->type == op) {
        token->value.op = *str;
        return 1;
    } else if (token->type == par) {
        token->value.par = *str;
        return 1;
    } else {
        char *endptr;
        token->value.num = strtod(str, &endptr);
        return endptr - str;
    }
}

Token *tokenise(char *str) {
    int count, type;
    int max_token_count = 10;
    int current_token_count = 0;

    Token *token = malloc(max_token_count * sizeof(Token));
    if (token == NULL) {
        perror("Failed to allocate memory.");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (current_token_count >= max_token_count) {
            max_token_count *= 2;
            Token *new_token = realloc(token, max_token_count * sizeof(Token));
            if (new_token == NULL) {
                free(token);
                perror("Failed to reallocate memory");
                exit(EXIT_FAILURE);
            }
            token = new_token;
        }
        type = check_type(str[i]);
        if (type != -1) {
            token[current_token_count].type = type;
            count = assign_value(&str[i], &token[current_token_count]);
            i += count - 1;
            current_token_count++;
        }

        token[current_token_count].type = end;
        token_count = current_token_count;
    }
    return token;
}

void parse(Token *t) {
    Stack *stack;
    Token *postfix;

    postfix = malloc(token_count * sizeof(Token));

    if (postfix == NULL) {
        perror("Failed to allocate memory.");
        exit(EXIT_FAILURE);
    }

    init_stack(stack);
    int postfix_count = 0;
    for (int i = 0; t[i].type == 4; i++) {
        if (t[i].type == 0) {
            postfix[postfix_count++] = t[i];
        } else if (t[i].type == par) {
            if (t[i].value.par == '(') {
                push(stack, t[i]);
            } else {
                for (int i = 0; stack->size == 0; i++) {
                    if (stack->data[i].type != par) {
                        postfix[postfix_count++] = pop(stack);
                    }
                    if (stack->data[i].type == par) {
                        if (stack->data->value.par == '(') {
                        }
                    }
                }
            }
        }
    }
}
