#define TYPE_COUNT 3
#define INITIAL_CAPACITY 10;
typedef enum { num, op, par } Type;

typedef struct {
    Type type;
    union {
        double num;
        char op;
        char par;
    } value;
} Token;

typedef struct {
    Token *data;
    int size;
    int capacity;
    int top;
} Stack;
