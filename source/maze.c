#include <stdlib.h>
#include <stdio.h>
#include "maze.h"

struct maze{
    int rows;
    int cols;
    unsigned char **cells;
};

Maze* maze_load(char *file_directory){
    FILE *f = fopen(file_directory, "rb");
    if(f == NULL)
        exit(printf("file %s not found.\n", file_directory));
    
    Maze *m = malloc(sizeof(Maze));
    fread(&m->rows, sizeof(int), 1, f);
    fread(&m->cols, sizeof(int), 1, f);
    m->cells = malloc(m->rows * sizeof(unsigned char*));

    int i;
    for(i = 0; i < m->rows; i++){
        m->cells[i] = malloc(m->cols * sizeof(unsigned char));
        fread(m->cells[i], sizeof(unsigned char), m->cols, f);
    }

    fclose(f);
    return m;
}

int maze_return_rows(Maze *m){
    return m->rows;
}

int maze_return_cols(Maze *m){
    return m->cols;
}

void maze_set_cell(Maze *m, int row, int col, int value){
    if(row < 0 || row >= m->rows || col < 0 || col >= m->cols)
        exit(printf("invalid position (%d , %d) in the maze with size (%d , %d)", row, col, m->rows, m->cols));

    m->cells[row][col] = value;
}

unsigned char maze_get_cell(Maze *m, int row, int col){
    if(row < 0 || row >= m->rows || col < 0 || col >= m->cols)
        exit(printf("invalid position (%d , %d) in the maze with size (%d , %d)", row, col, m->rows, m->cols));

    return m->cells[row][col];
}

void maze_destroy(Maze *m){
    int i;
    for(i = 0; i < m->rows; i++)
        free(m->cells[i]);

    free(m->cells);
    free(m);
}

void maze_display(Maze *m){
    int i, j;
    for(i = 0; i < m->rows; i++){
        printf("| ");
        for(j = 0; j < m->cols; j++)
            _maze_display_cell(maze_get_cell(m, i, j));
        printf("|\n");
    }
}

void _maze_display_cell(unsigned char val){
    switch (val){
    case FREE:
        printf(". ");
        break;
    case OCCUPIED:
        printf("# ");
        break;
    case FRONTIER:
        printf("F ");
        break;
    case EXPANDED:
        printf("X ");
        break;
    case PATH:
        printf("O ");
        break;
    case START:
        printf("I ");
        break;
    case END:
        printf("[]");
        break;
    default:
        printf("Invalid cell type.\n");
    }
}
