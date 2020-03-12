CC = gcc
CFLAGS = -Wall -Og

all: p6 p6.so

p6: p6.c
	$(CC) $(CFLAGS) -rdynamic -o p6 p6.c -ldl
p6.so: timestamp.c
	$(CC) $(CFLAGS) -shared -fPIC -o p6.so timestamp.c