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
} Element;

typedef struct {
    Element *data;
    int top;
    size_t size;
    size_t capacity;
} Stack;

Element *tokenise(char *str);
void initStack(Stack *s);
void freeStack(Stack *s);
void push(Stack *s, Element data);
Element pop(Stack *s);
Element peek(Stack *s);
bool isEmpty(Stack *s);
bool isFull(Stack *s);

int main(int argc, char *argv[]) {
    char test[30] = "3+ 43.67 -(6/2.5) * 2.2";
    Element *tokens = tokenise(test);
    printf("%s\n", test);
    if (tokens == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; tokens[i].type != END; i++) {
        if (tokens[i].type == OPERAND) {
            printf("Operand: %lf\n", tokens[i].value.num);
        } else if (tokens[i].type == OPERATOR) {
            printf("Operator: %c\n", tokens[i].value.op);
        }
    }

    free(tokens);
    return EXIT_SUCCESS;
}

Element *tokenise(char *str) {
    Element *token = (Element *)malloc(INITIAL_CAPACITY * sizeof(Element));
    int token_count = 0;
    int max_length = INITIAL_CAPACITY;
    if (token == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i <= strlen(str); i++) {
        if (token_count == max_length) {
            max_length *= 2;
            Element *tmp_token = (Element *)realloc(token, max_length * sizeof(Element));
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

void initStack(Stack *s) {
    s->capacity = INITIAL_CAPACITY;
    s->data = malloc(s->capacity * sizeof(Element));
    if (s->data == NULL) {
        fprintf(stderr, "Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    s->top = -1;
    s->size = 0;
}
void freeStack(Stack *s) { free(s); }
void push(Stack *s, Element data) {
    if (s->size == s->capacity) {
        s->capacity *= 2;
        Element *tmp = realloc(s->data, s->capacity * sizeof(Element));
        if (tmp == NULL) {
            fprintf(stderr, "Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        s->data = tmp;
    }
    s->data[++s->top] = data;
    s->size++;
    s->data[s->top + 1].type = END;
}
bool isEmpty(Stack *s);
bool isFull(Stack *s);
Element pop(Stack *s) {
    if (isEmpty(s)) {
        fprintf(stderr, "Stack is empty: POP");
        exit(EXIT_FAILURE);
    }
    Element tmp = s->data[s->top];
    s->data[s->top--].type = END;
    return tmp;
}
Element peek(Stack *s) {}
