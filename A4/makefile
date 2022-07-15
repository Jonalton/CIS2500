 CC=gcc
CFLAGS=-Wall -ansi -Iincludes

all: main.o writeContact.o readStrings.o editContact.o deleteContact.o sort_lastName.o
	$(CC) $(CFLAGS) -o  bin/contactList bin/main.o bin/writeContact.o bin/readStrings.o bin/editContact.o bin/deleteContact.o bin/sort_lastName.o

main.o: src/main.c includes/contactList.h
	$(CC) $(CFLAGS) -c src/main.c -o bin/main.o

writeContact.o: src/writeContact.c includes/struct.h
	$(CC) $(CFLAGS) -c src/writeContact.c -o bin/writeContact.o

readStrings.o: src/readStrings.c includes/struct.h
	$(CC) $(CFLAGS) -c src/readStrings.c -o bin/readStrings.o

editContact.o: src/editContact.c includes/struct.h
	$(CC) $(CFLAGS) -c src/editContact.c -o bin/editContact.o

deleteContact.o: src/deleteContact.c includes/struct.h
	$(CC) $(CFLAGS) -c src/deleteContact.c -o bin/deleteContact.o

sort_lastName.o: src/sort_lastName.c includes /struct.h
	$(CC) $(CFLAGS) -c src/sort_lastName.c -o bin/sort_lastName.o

clean: 
	rm bin/*
