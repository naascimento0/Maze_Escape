CC = gcc

all:
	$(CC) main.c source/*.c -o exec
	./exec
