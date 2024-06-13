CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -Werror -02 -g -std=c11 -pedantic
LDFLAGS = -lm
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
EXEC = ccalc

all: $(EXEC)

$(EXEC): $(OBJ)
    $(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJ) $(EXEC)

.PHONY: all clean
