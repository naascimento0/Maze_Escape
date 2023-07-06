#ifndef SEARCHS_H_
#define SEARCHS_H_

#include "maze.h"

typedef struct{
    int x;
    int y;
}Cell;

typedef struct{
    Cell *path;
    double path_cost;
    int path_size;
    int expanded_nodes;
    int sucess;
}SearchResultData;


SearchResultData search_result_data_create();


#endif
