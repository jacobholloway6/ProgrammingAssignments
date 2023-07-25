# A Makefile for Program 0, CS480

PROGRAM = testbbuffer
CC = gcc
CFLAGS = -g -std=c99 

${PROGRAM}:	${PROGRAM}.o bbuffer.o
		${CC} -o ${PROGRAM} ${PROGRAM}.o bbuffer.o -lpthread -lm



clean:
		rm -f *.o ${PROGRAM}

${PROGRAM}.o bbuffer.o: bbuffer.h
