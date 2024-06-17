#include "global_vars.h"

void init_stack(Stack *s);
void push(Stack *s, Token data);
Token pop(Stack *s);
Token *peek(Stack *s);
int is_empty(Stack *s);
int is_full(Stack *s);
int size(Stack *s);
int capacity(Stack *s);
void free_stack(Stack *s);
