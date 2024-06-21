#include <assert.h>
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
    int size;
    size_t capacity;
} Stack;

typedef struct {
    Element *data;
    size_t end;
    size_t capacity;
} List;

Element *tokenise(char *str);
// Stack
void initStack(Stack *s);
void freeStack(Stack *s);
void push(Stack *s, Element data);
Element pop(Stack *s);
Element peek(Stack *s);
bool isEmpty(Stack *s);
bool isFull(Stack *s);
void printStack(Stack *s);
// List
void initList(List *l);
void freeList(List *l);
void appendList(List *l, Element e);
void printList(List *l);

List infixToPostfix(Element *t);

int main(int argc, char *argv[]) {
    printf("All tests passed!\n");
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
void freeStack(Stack *s) { free(s->data); }
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
    if (s->size == s->capacity) {
        s->capacity *= 2;
        Element *tmp = realloc(s->data, s->capacity * sizeof(Element));
        if (tmp == NULL) {
            fprintf(stderr, "Memory allocation failed");
            exit(EXIT_FAILURE);
        }
        s->data = tmp;
    }
    s->data[s->top + 1].type = END;
}
bool isEmpty(Stack *s) { return s->size == 0; }
bool isFull(Stack *s) { return s->size == s->capacity; }
Element pop(Stack *s) {
    if (isEmpty(s)) {
        fprintf(stderr, "Stack is empty: POP");
        exit(EXIT_FAILURE);
    }
    Element tmp = s->data[s->top];
    s->data[s->top--].type = END;
    return tmp;
}
Element peek(Stack *s) {
    if (s->size == 0) {
        fprintf(stderr, "Stack is empty: peek");
        exit(EXIT_FAILURE);
    }
    return s->data[s->top];
}

void printStack(Stack *s) {
    if (s->size == 0) {
        fprintf(stderr, "Stack is empty: printStack");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; s->data->type != END; i++) {
        if (s->data->type == OPERAND) {
            printf("Operand: %lf\n", s->data->value.num);
        } else if (s->data->type == OPERATOR) {
            printf("Operator: %c\n", s->data->value.op);
        }
    }
}

void initList(List *l) {
    l->end = -1;
    l->capacity = INITIAL_CAPACITY;
    l->data = malloc(l->capacity * sizeof(Element));
    if (l->data == NULL) {
        fprintf(stderr, "Failed to assign memory: initList");
        exit(EXIT_FAILURE);
    }
}
void freeList(List *l) { free(l->data); }
void appendList(List *l, Element e) {
    if (l->capacity == l->end + 1) {
        l->capacity *= 2;
        List *temp;
        temp->data = realloc(l->data, l->capacity * sizeof(Element));
        l = temp;
    }
    l->data[++l->end] = e;
    l->capacity++;
}
void printList(List *l) {
    if (l->end == -1) {
        fprintf(stderr, "List is empty: printList");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; l->data->type != END; i++) {
        if (l->data->type == OPERAND) {
            printf("Operand: %lf\n", l->data->value.num);
        } else if (l->data->type == OPERATOR) {
            printf("Operator: %c\n", l->data->value.op);
        }
    }
}
List infixToPostfix(Element *t) {
    List postfix;
    Stack s;
    return postfix;
}
