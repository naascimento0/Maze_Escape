CC = gcc

all:
	$(CC) main.c source/*.c source/data_structures/*.c -o exec -Wall
	./exec
