#
# CS 11: Makefile for C track, assignment 5.
#

CC     = gcc
CFLAGS = -g -Wall -Wstrict-prototypes -ansi -pedantic

all: point_cell_auto array_cell_auto

point_cell_auto: point_cell_auto.o memcheck.o
	$(CC) point_cell_auto.o memcheck.o -o point_cell_auto

array_cell_auto: array_cell_auto.o memcheck.o
	$(CC) array_cell_auto.o memcheck.o -o array_cell_auto

memcheck.o: memcheck.c memcheck.h
	$(CC) $(CFLAGS) -c memcheck.c

check:
	c_style_check array_cell_auto.c
	c_style_check point_cell_auto.c

clean:
	rm -f array_cell_auto *.o
	rm -f point_cell_auto *.o