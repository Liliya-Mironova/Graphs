CC=g++

CFLAGS=-c -Wall -std=gnu++11

all: hw8

hw8: main.o
	$(CC) main.o -o hw8

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

clean:
	rm -rf *.o hw8