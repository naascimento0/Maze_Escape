CC = gcc

all:
	$(CC) main.c source/*.c source/data_structures/*.c -o exec -Wall -Wextra -Wno-unused-result -Wno-unused-parameter -g -lm
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./exec <data/input/entrada
	
clean:
	rm -r exec
	
	

