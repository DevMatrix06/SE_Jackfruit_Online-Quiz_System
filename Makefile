CC     = gcc
CFLAGS = -Wall -std=c99 -Iinclude -MMD -MP
SRC    = $(wildcard src/*.c)
OBJ    = $(SRC:.c=.o)

quiz: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

test: tests/test_score.c src/score.c
	$(CC) $(CFLAGS) -o tests/test_score tests/test_score.c src/score.c
	./tests/test_score

clean:
	rm -f src/*.o src/*.d quiz quiz.exe tests/test_score tests/test_score.exe

.PHONY: clean test

-include $(OBJ:.o=.d)
