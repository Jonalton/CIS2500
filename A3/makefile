CC=gcc
CFLAGS=-Wall -ansi -Iincludes

all: main.o freeStrings.o readStrings.o storeStrings.o
	$(CC) $(CFLAGS) -o  bin/contactList bin/main.o bin/freeStrings.o bin/readStrings.o bin/storeStrings.o

main.o: src/main.c includes/contactList.h
	$(CC) $(CFLAGS) -c src/main.c -o bin/main.o

freeStrings.o: src/freeStrings.c includes/struct.h
	$(CC) $(CFLAGS) -c src/freeStrings.c -o bin/freeStrings.o

readStrings.o: src/readStrings.c includes/struct.h
	$(CC) $(CFLAGS) -c src/readStrings.c -o bin/readStrings.o

storeStrings.o: src/storeStrings.c includes/struct.h
	$(CC) $(CFLAGS) -c src/storeStrings.c -o bin/storeStrings.o

clean: 
	rm bin/*
