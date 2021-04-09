CC=gcc
FLAGS=-Wall -Wextra -Werror -g

decrypt: decrypt.c
	$(CC) $^ -o $@ $(FLAGS)

.PHONY: clean
clean:
	rm -rf decrypt