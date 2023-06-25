#include <stdlib.h>
#include <stdio.h>
#include "source/maze.h"

int main()
{
    char maze_file[100];

    scanf("%s", maze_file);

    Maze *m = maze_load(maze_file);
    
    maze_display(m);

    maze_destroy(m);

    return 0;
}