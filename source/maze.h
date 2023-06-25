#ifndef MAZE_H_
#define MAZE_H_

typedef struct maze Maze;

typedef enum{
    FREE = 0,
    OCCUPIED = 1,
    FRONTIER = 2,
    EXPANDED = 3,
    PATH = 4,
    START = 5,
    END = 6
}CellType;

Maze* maze_load(char *file_directory);
int maze_return_rows(Maze *m);
int maze_return_cols(Maze *m);
void maze_set_cell(Maze *m, int row, int col, int value);
unsigned char maze_get_cell(Maze *m, int row, int col);
void maze_destroy(Maze *m);
void maze_display(Maze *m);
void _maze_display_cell(unsigned char val);


#endif