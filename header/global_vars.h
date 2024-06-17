#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

#define TYPE_COUNT 3
#define INITIAL_CAPACITY 10;
typedef enum { OPERAND, OPERATOR, END } Type;

typedef struct {
    Type type;
    union {
        double operand;
        char _operator;
    } value;
} Token;

typedef struct {
    Token *data;
    int size;
    int capacity;
    int top;
} Stack;

#endif // !GLOBAL_VARS_H
