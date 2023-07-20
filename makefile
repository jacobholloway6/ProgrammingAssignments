# A Makefile for Program 2, CS480 
# This is a sample, you may need to modify this file to make it works
# Author: Zheng Li

PROGRAM =testmulthreads
CC = gcc
CFLAGS = -g -std=c99 

${PROGRAM}:	${PROGRAM}.o alphabetcountmulthreads.o
		${CC} -o ${PROGRAM} ${PROGRAM}.o alphabetcountmulthreads.o -lpthread -lm

alphabetcountmulthreads.o ${PROGRAM}.o:	count.h


clean:
		rm -f *.o ${PROGRAM}		
