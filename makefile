CC=gcc
CFLAGS=-I.

new: aplication.c Serialcommunicate.c socketcommunicate.c sim800l.c
	$(CC) -o new aplication.c Serialcommunicate.c socketcommunicate.c sim800l.c -I.