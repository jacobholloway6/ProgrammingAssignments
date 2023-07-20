# A Makefile for Program 0, CS570

all: testalphabet testspecial

OTHER_ALPHA__OBJS = testalphabetcount.o alphabetcount.o
OTHER_SPECIAL__OBJS = testspecialcharcount.o specialcharcount.o

CC = gcc
CFLAGS = -g -std=c99

testalphabet:	${OTHER_ALPHA__OBJS}
		${CC} -o testalphabet ${OTHER_ALPHA__OBJS}


testspecial: ${OTHER_SPECIAL__OBJS}
	 ${CC} -o testspecial ${OTHER_SPECIAL__OBJS}

${OTHER_SPECIAL__OBJS} ${OTHER_SPECIAL__OBJS}:count.h

clean:
		rm -f *.o testalphabet testspecial
