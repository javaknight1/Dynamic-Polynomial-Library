# Sample makefile
# D. Frey
# Spring 2011
##

CC = /usr/bin/gcc
CFLAGS = -Wall -std=c99 -g

# name of the executable to be created
PROJECT = Project4

# list of all .c files
SRCS = Project4.c polynomials.c

#list of all .h files
HDRS = polynomials.h

# list of .o files
OBJS = Project4.o polynomials.o

# the first rule is the default rule
# build the executable from the .o files
$(PROJECT) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROJECT)

# a separate rule to compile each .c file
Project4.o: Project4.c polynomials.h
	$(CC) $(CFLAGS) -c Project4.c

polynomials.o : polynomials.c polynomials.h
	$(CC) $(CFLAGS) -c polynomials.c

# some handy commands that you can "make"
clean:
	rm -fv core* $(PROJECT) $(OBJS)

cleaner: clean
	rm -fv #* *~

