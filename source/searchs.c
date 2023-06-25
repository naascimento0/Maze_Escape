#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "searchs.h"

struct cell{
    int x;
    int y;
};

struct searchresult{
    Cell *path;
    double path_cost;
    int path_size;
    int expanded_nodes;
    int sucess;
};

SearchResult search_result_create(){
    SearchResult sr;
    sr.path = NULL;
    sr.path_cost = 0;
    sr.path_size = 0;
    sr.expanded_nodes = 0;
    sr.sucess = 0;
    return sr;
}

SearchResult a_star_search(Maze *m, Cell start, Cell end){
    SearchResult sr;
    // TODO!
    return sr;
}

SearchResult breadth_first_search(Maze *m, Cell start, Cell end){
    SearchResult sr;
    // TODO!
    return sr;
}

SearchResult depth_first_search(Maze *m, Cell start, Cell end){
    SearchResult sr;
    // TODO!
    return sr;
}