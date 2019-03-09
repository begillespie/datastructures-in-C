CC = gcc
CFLAGS = -Wall -std=c99 -g
OBJECTS = avl.o driver.o
EXECUTABLES = driver

all : $(EXECUTABLES)

driver : avl.o

avl.o : avl.h bstnode.h

clean :
	-rm -f $(EXECUTABLES) $(OBJECTS)
