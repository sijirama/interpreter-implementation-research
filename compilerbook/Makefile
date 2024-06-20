
# Variables
CC = g++
FLEX = flex
CFLAGS = -Wall -Wextra -Wno-unused-function -std=c++11
LDFLAGS =

# Targets
all: scanner

scanner: lex.yy.o main.o
	$(CC) $(LDFLAGS) -o scanner lex.yy.o main.o

lex.yy.o: lex.yy.c token.h
	$(CC) $(CFLAGS) -c lex.yy.c

main.o: main.cpp token.h
	$(CC) $(CFLAGS) -c main.cpp token.h

lex.yy.c: scanner.lex
	$(FLEX) -o lex.yy.c scanner.lex

clean:
	rm -f scanner lex.yy.c lex.yy.o main.o token.h.gch

# Phony targets
.PHONY: all clean

