 # Soubor: Makefile
 # Reseni IJC-DU2, 18.4.2018
 # Autor: Jakub Frejlach (xfrejl00), FIT

CC=gcc
CPP=g++
CFLAGS= -std=c99 -Wall -Wextra -pedantic
CPPFLAGS= -std=c++11 -pedantic -Wall
LIBFILES=htab_init.o htab_hash_function.o htab_size.o htab_bucket_count.o htab_lookup_add.o htab_find.o htab_remove.o htab_clear.o htab_free.o htab_foreach.o htab_move.o

all: tail wordcount wordcount-dynamic

tail: tail.c tail2.cc
	$(CC) $(CFLAGS) tail.c -o tail
	$(CPP) $(CPPFLAGS) tail2.cc -o tail2

wordcount: wordcount.o io.o libhtable.a libhtable.so
	$(CC) $(CFLAGS) io.o wordcount.o libhtable.a -o wordcount
	$(CC) $(CFLAGS) -L. io.o wordcount.o libhtable.so -o wordcount-dynamic

io.o:
	$(CC) $(CFLAGS) -c io.c -o io.o

wordcount.o: wordcount.c htab.h
	$(CC) $(CFLAGS) -c wordcount.c -o wordcount.o

################################### Knihovny ###################################

libhtable.a: $(LIBFILES)
	ar crs libhtable.a $(LIBFILES)

libhtable.so: $(LIBFILES)
	$(CC) $(CFLAGS) -shared -fPIC -o libhtable.so $(LIBFILES)

################################### htab.h ###################################

htab_init.o: htab_init.c htab.h htab-private.h
	$(CC) $(CFLAGS) -fPIC -c htab_init.c -o htab_init.o

htab_clear.o:	htab_clear.c htab.h htab-private.h
	$(CC) $(CFLAGS) -fPIC -c htab_clear.c -o htab_clear.o

htab_foreach.o:	htab_foreach.c htab.h htab-private.h
	$(CC) $(CFLAGS) -fPIC -c htab_foreach.c -o htab_foreach.o

htab_free.o: htab_free.c htab.h htab-private.h
	$(CC) $(CFLAGS) -fPIC -c htab_free.c -o htab_free.o

htab_lookup_add.o: htab_lookup_add.c htab.h htab-private.h
	$(CC) $(CFLAGS) -fPIC -c htab_lookup_add.c -o htab_lookup_add.o

htab_remove.o: htab_remove.c htab.h htab-private.h
	$(CC) $(CFLAGS) -fPIC -c htab_remove.c -o htab_remove.o

htab_hash_function.o: htab_hash_function.c htab.h htab-private.h
	$(CC) $(CFLAGS) -fPIC -c htab_hash_function.c -o htab_hash_function.o

htab_size.o: htab_size.c htab.h htab-private.h
	$(CC) $(CFLAGS) -fPIC -c htab_size.c -o htab_size.o

htab_bucket_count.o: htab_bucket_count.c htab.h htab-private.h
	$(CC) $(CFLAGS) -fPIC -c htab_bucket_count.c -o htab_bucket_count.o

htab_move.o: htab_move.c htab.h htab-private.h
	$(CC) $(CFLAGS) -fPIC -c htab_move.c -o htab_move.o

htab_find.o: htab_find.c htab.h htab-private.h
	$(CC) $(CFLAGS) -fPIC -c htab_find.c -o htab_find.o

################################### clean ###################################

clean:
	rm -f *.o tail tail2 wordcount wordcount-dynamic libhtable.a libhtable.so
