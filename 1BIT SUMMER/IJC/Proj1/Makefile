SHELL = /bin/bash
CC=gcc
CFLAGS=-O2 -std=c99 -Wall -Wextra -pedantic
LDFLAGS=-lm
PROJ=primes
INLINE=primes-i
DECODE=steg_decode

all: primes steg_decode
steg_decode: steg_decode.c error.c ppm.c ppm.h eratosthenes.c bit_array.h
	$(CC) $(CFLAGS) $(DECODE).c -o $(DECODE) $(LDFLAGS)
primes: primes.c eratosthenes.c bit_array.h error.c
	$(CC) $(CFLAGS) $(PROJ).c -o $(PROJ) $(LDFLAGS)
	$(CC) $(CFLAGS) $(PROJ).c -o $(INLINE) $(LDFLAGS) -DUSE_INLINE
run: primes
	time ./primes
	time ./primes-i
clean:
	rm $(PROJ)
	rm $(INLINE)
	rm $(DECODE)
zip:
	zip xfrejl00.zip *.c *.h Makefile
