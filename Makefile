CC     = gcc
CFLAGS = -Wall -std=c99 -Iinclude
SRC    = $(wildcard src/*.c)
OBJ    = $(SRC:.c=.o)

quiz: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o quiz quiz.exe

.PHONY: clean
