CC=gcc
CFLAGS=-pedantic -Wall -Wextra

all: drift repeat

drift: drift.c
	$(CC) drift.c -o bin/drift

repeat: repeat.o btree.o
	$(CC) $(CFLAGS) -o bin/repeat repeat.o btree.o

repeat.o: repeat.c btree.h
	$(CC) $(CFLAGS) -c repeat.c

btree.o: btree.c btree.h
	$(CC) $(CFLAGS) -c btree.c

clean: 
	rm bin/* *.o
