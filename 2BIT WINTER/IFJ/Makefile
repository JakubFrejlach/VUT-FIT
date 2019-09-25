CC=gcc
CFLAGS= -std=c99 -Wall -Wextra -pedantic -g

PHONY:
	$(CC) $(CFLAGS) expressions.c expressions.h parser.c parser.h symtable.c symtable.h scanner.c scanner.h main.c main.h dstring.c dstring.h error.c error.h generate.c stack.c -o compiler

scanner-test:
	$(CC) $(CFLAGS) error.c error.h dstring.c dstring.h scanner.c scanner.h tests/scanner-test.c -o tests/scanner-test

test: scanner-test
	./tests/scanner-test
	./tests/parser-test.sh
