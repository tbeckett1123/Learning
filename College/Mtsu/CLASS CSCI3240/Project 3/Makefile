CC=gcc
CFLAGS=-g -01 -Wall

all:	client server

client:	client.c csapp.h csapp.c
	${CC} ${CFLAGS2} client.c csapp.c -o client
server:	server.c csapp.h csapp.c
	${CC} ${CFLAGS2} server.c csapp.c -o server
clean:
	rm -f *.o *~ *.exe client server csapp.o