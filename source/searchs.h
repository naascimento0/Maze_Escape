#ifndef SEARCHS_H_
#define SEARCHS_H_

#include "maze.h"

typedef struct cell{
    int x;
    int y;
    void *parent;
}Cell;

typedef struct{
    Cell *path;
    double path_cost;
    int path_length;
    int expanded_nodes;
    int sucess;
}SearchResultData;


SearchResultData search_result_data_create();

int cell_is_equal(Cell a, Cell b);

Cell* cell_construct(int x, int y, void *parent);

SearchResultData reverse_search_result_path(SearchResultData search_result);

SearchResultData breadth_first_search(Maze *m, Cell start, Cell end);

SearchResultData depth_first_search(Maze *m, Cell start, Cell end);

#endif
