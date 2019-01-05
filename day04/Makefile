CC=gcc
CFLAGS=-pedantic -Wall -Wextra

all: sleep 

sleep: sleep.c event.h event.o binaryguard.h binaryguard.o
	$(CC) $(CFLAGS) sleep.c event.o binaryguard.o -o bin/sleep

event.o: event.c event.h
	$(CC) $(CFLAGS) -c event.c

binaryguard.o: binaryguard.c binaryguard.h
	$(CC) $(CFLAGS) -c binaryguard.c
