CC     = gcc
CFLAGS = -Wall -std=c99 -Iinclude -MMD -MP
SRC    = $(wildcard src/*.c)
OBJ    = $(SRC:.c=.o)

quiz: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o src/*.d quiz quiz.exe

.PHONY: clean

-include $(OBJ:.o=.d)
