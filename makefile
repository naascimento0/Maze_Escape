CC = gcc

all:
	$(CC) main.c source/*.c source/data_structures/*.c -o exec -Wall -lm
	valgrind --leak-check=full --track-origins=yes ./exec <data/input/in_maze10x10_obstaculos_1.txt
clean:
	rm -r exec
