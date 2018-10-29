all: list.o linked-list.o
	gcc -Wall -o linked-pairs list.o linked-list.o

list.o: list.h list.c
	gcc -Wall -c list.h list.c

linked-list.o: linked-list.c
	gcc -Wall -c linked-list.c
