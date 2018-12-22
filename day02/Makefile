CC=gcc
CFLAGS=-pedantic -Wall -Wextra -std=c99

all: checksum fabricsearch

checksum: checksum.c
	$(CC) $(CFLAGS) checksum.c -o bin/checksum

fabricsearch: fabricsearch.c fabricsearch.h
	$(CC) $(CFLAGS) fabricsearch.c -o bin/fabricsearch
