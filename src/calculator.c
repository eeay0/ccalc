#include "../include/calculator.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_input() {
    char *input = NULL;
    char *token = NULL;
    int tok_c = 0;
    size_t len = 0;
    ssize_t read; // ssize_t is the correct type for getline's return value
    int p_op;

    printf("Choice the operation\n1. Add/Sub/Mult/Div\n");
    p_op = getchar();

    // Consume the newline character left in the input buffer by getchar
    getchar();

    read = getline(&input, &len, stdin);

    if (read != -1) {
        token = strtok(input, " ");
    } else {
        printf("Error reading line.\n");
    }

    free(input); // Free the allocated memory
}
