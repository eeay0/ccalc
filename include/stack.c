#include "../header/global_vars.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void init_stack(Stack *s) {
    s->capacity = INITIAL_CAPACITY;
    s->size = 0;
    s->top = -1;

    s->data = malloc(s->capacity * sizeof(Token));
    if (s->data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

void push(Stack *s, Token data) {
    if (s->size >= s->capacity) {
        s->capacity = s->capacity * 2;
        Token *temp = realloc(s->data, s->capacity * sizeof(Token));
        if (temp == NULL) {
            free(s->data);
            perror("Failed to reallocate memory");
            exit(EXIT_FAILURE);
        }
        s->data = temp;
    }
    s->data[++s->top] = data;
    s->size++;
}

Token pop(Stack *s) {
    if (s->size == 0) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    Token data = s->data[s->top--];
    s->size--;
    return data;
}

Token *peek(Stack *s) {
    if (s->size == 0) {
        fprintf(stderr, "Stack is empty");
        exit(EXIT_FAILURE);
    }
    return &s->data[s->top];
}

int is_empty(Stack *s) {
    if (s->size == 0) {
        return 1;
    } else {
        return 0;
    }
}

int is_full(Stack *s) {
    if (s->size == s->capacity) {
        return 1;
    } else {
        return 0;
    }
}

int size(Stack *s) { return s->size; }
int capacity(Stack *s) { return s->capacity; }
void free_stack(Stack *s) { free(s); }
