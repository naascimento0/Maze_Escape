#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "searchs.h"
#include "data_structures/deque.h"

SearchResultData search_result_data_create(){
	SearchResultData search_result;
	search_result.path = NULL;
	search_result.path_cost = 0;
	search_result.path_length = 0;
	search_result.expanded_nodes = 0;
	search_result.sucess = 0;
    return search_result;
}

int cell_is_equal(Cell a, Cell b){
	return a.x == b.x && a.y == b.y;
}

Cell* cell_construct(int x, int y, void *parent){
	Cell *c = malloc(sizeof(Cell));
	c->x = x;
	c->y = y;
	c->parent = parent;
	return c;
}

// SearchResult a_star_search(Maze *m, Cell start, Cell end){
//     SearchResult sr;
//     // TODO!
//     return sr;
// }

SearchResultData breadth_first_search(Maze *m, Cell start, Cell end){
	SearchResultData search_result = search_result_data_create();

	int neighbours[8][2] = {{-1,0}, {-1, 1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0, -1}, {-1,-1}};

	Cell *cell = cell_construct(start.x, start.y, NULL);
	Deque *expand = deque_construct();
	deque_push_back(expand, cell);

	int allocated_size = 40;
	Cell **expanded_cells_array = malloc(allocated_size * sizeof(Cell*));

	while(deque_size(expand)){
		cell = deque_pop_front(expand);
		maze_set_cell(m, cell->x, cell->y, EXPANDED);
		search_result.expanded_nodes++;

		if(allocated_size == search_result.expanded_nodes){
			allocated_size *= 2;
			expanded_cells_array = realloc(expanded_cells_array, allocated_size * sizeof(Cell*));
		}

		if(cell_is_equal(*cell, end)){
			search_result.sucess = 1;
			break;
		}

		int i;
		for(i = 0; i < 8; i++){
			int x = neighbours[i][0] + cell->x;
			int y = neighbours[i][1] + cell->y;

			if(x < 0 || x >= maze_return_rows(m) || y < 0 || y >= maze_return_cols(m))
				continue;
			
			int verify = maze_get_cell(m, x, y);
			if(verify == OCCUPIED || verify == EXPANDED || verify == FRONTIER)
				continue;
			
			Cell *new_cell = cell_construct(x, y, cell);
			deque_push_back(expand, new_cell);
			maze_set_cell(m, new_cell->x, new_cell->y, FRONTIER);
			expanded_cells_array[search_result.expanded_nodes - 1] = new_cell;
		}
	}
	
	if(search_result.sucess){
		Cell *current = cell;
		int allocated = search_result.expanded_nodes / 2;
		search_result.path = calloc(allocated, sizeof(Cell));

		while(current != NULL){
			if(search_result.path_length >= allocated){
				allocated *= 2;
				search_result.path = realloc(search_result.path, allocated * sizeof(Cell));
			}

			Cell aux = {current->x, current->y};
			search_result.path[search_result.path_length++] = aux;
			Cell *parent = current->parent;
			if(parent != NULL)
				search_result.path_cost += sqrt((pow(current->x - parent->x, 2) + pow(current->y - parent->y, 2)));

			current = current->parent;
		}
	}

	int i;
	for(i = 0; i < search_result.expanded_nodes; i++)
		free(expanded_cells_array[i]);

	deque_destroy(expand);
	return search_result;
 }

// SearchResult depth_first_search(Maze *m, Cell start, Cell end){
//     SearchResult sr;
//     // TODO!
//     return sr;
// }
