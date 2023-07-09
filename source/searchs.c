#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "searchs.h"
#include "data_structures/deque.h"
#include "data_structures/stack.h"
#include "data_structures/heap.h"
#include "data_structures/hash.h"

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

SearchResultData reverse_search_result_path(SearchResultData search_result){
	Stack *s = stack_construct();
	int i;
	for(i = 0; i < search_result.path_length; i++){
		Cell temp = search_result.path[i];
		Cell *aux = malloc(sizeof(Cell));
		aux->x = temp.x;
		aux->y = temp.y;
		stack_push(s, aux);
	}

	for(i = 0; i < search_result.path_length; i++){
		Cell *aux = stack_pop(s);
		Cell temp = {aux->x, aux->y, NULL};
		search_result.path[i] = temp;
		free(aux);
	}

	stack_destroy(s);
	return search_result;
}

int _cell_hash(HashTable *h, void *key)
{
    Cell *c = (Cell*)key;
    return ((c->x * 83) ^ (c->y * 97)) % hash_table_size(h);
}

int _cell_cmp(void *c1, void *c2)
{
	Cell *a = (Cell*)c1;
	Cell *b = (Cell*)c2;

    if (a->x == b->x && a->y == b->y)
        return 0;
    else
        return 1;
}

double _accumulated_cost(Cell *new_cell){
	double accumulated_cost = 0;
	while(new_cell->parent != NULL){
		Cell *temp = (Cell*)new_cell->parent;
		accumulated_cost += sqrt(pow(new_cell->x - temp->x, 2) + pow(new_cell->y - temp->y, 2));
		new_cell = new_cell->parent;
	}

	return accumulated_cost;
}

SearchResultData a_star_search(Maze *m, Cell start, Cell end){
	SearchResultData search_result = search_result_data_create();

	int neighbours[8][2] = {{-1,0}, {-1, 1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0, -1}, {-1,-1}};

	HashTable *hash = hash_table_construct(19, _cell_hash, _cell_cmp);
	Heap *expand = heap_construct(hash);

	Cell *cell = cell_construct(start.x, start.y, NULL);
	double heuristic = sqrt(pow(start.x - end.x, 2) + pow(start.y - end.y, 2));
	heap_push(expand, cell, heuristic);

	int allocated_size = 40;
	Cell **expanded_cells_array = calloc(allocated_size, sizeof(Cell*));

	while(!heap_empty(expand)){
		cell = heap_pop(expand);
		maze_set_cell(m, cell->x, cell->y, EXPANDED);
		search_result.expanded_nodes++;

		if(allocated_size <= search_result.expanded_nodes){
			allocated_size *= 2;
			expanded_cells_array = realloc(expanded_cells_array, allocated_size * sizeof(Cell*));
		}

		expanded_cells_array[search_result.expanded_nodes - 1] = cell;

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

			heuristic = sqrt(pow(x - end.x, 2) + pow(y - end.y, 2));
			Cell *new_cell = cell_construct(x, y, cell);
			heap_push(expand, new_cell, heuristic + _accumulated_cost(new_cell));
			maze_set_cell(m, new_cell->x, new_cell->y, FRONTIER);
		}
	}

	if(search_result.sucess){
		Cell *current = cell;
		int allocated = search_result.expanded_nodes / 4;
		search_result.path = calloc(allocated, sizeof(Cell));

		while(current != NULL){
			if(search_result.path_length >= allocated){
				allocated *= 2;
				search_result.path = realloc(search_result.path, allocated * sizeof(Cell));
			}

			Cell aux = {current->x, current->y, NULL};
			search_result.path[search_result.path_length++] = aux;
			Cell *parent = current->parent;
			if(parent != NULL)
				search_result.path_cost += sqrt((pow(current->x - parent->x, 2) + pow(current->y - parent->y, 2)));

			current = current->parent;
		}

		search_result = reverse_search_result_path(search_result);
	}

	int i;
	for(i = 0; i < search_result.expanded_nodes; i++)
		free(expanded_cells_array[i]);

	free(expanded_cells_array);

	HashTableIterator *it = hash_table_iterator(hash);
	while (!hash_table_iterator_is_over(it)){
		HashTableItem *item = hash_table_iterator_next(it);
		Cell *c = (Cell*)item->key;
		int *pos = (int *)item->value;
		free(c);
		free(pos);
	}

	hash_table_iterator_destroy(it);
	heap_destroy(expand);
	return search_result;
}

SearchResultData breadth_first_search(Maze *m, Cell start, Cell end){
	SearchResultData search_result = search_result_data_create();

	int neighbours[8][2] = {{-1,0}, {-1, 1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0, -1}, {-1,-1}};

	Cell *cell = cell_construct(start.x, start.y, NULL);
	Deque *expand = deque_construct();
	deque_push_back(expand, cell);

	int allocated_size = 40;
	Cell **expanded_cells_array = calloc(allocated_size, sizeof(Cell*));

	while(deque_size(expand)){
		cell = deque_pop_front(expand);
		maze_set_cell(m, cell->x, cell->y, EXPANDED);
		search_result.expanded_nodes++;

		if(allocated_size <= search_result.expanded_nodes){
			allocated_size *= 2;
			expanded_cells_array = realloc(expanded_cells_array, allocated_size * sizeof(Cell*));
		}

		expanded_cells_array[search_result.expanded_nodes - 1] = cell;

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
		}
	}
	
	if(search_result.sucess){
		Cell *current = cell;
		int allocated = search_result.expanded_nodes / 4;
		search_result.path = calloc(allocated, sizeof(Cell));

		while(current != NULL){
			if(search_result.path_length >= allocated){
				allocated *= 2;
				search_result.path = realloc(search_result.path, allocated * sizeof(Cell));
			}

			Cell aux = {current->x, current->y, NULL};
			search_result.path[search_result.path_length++] = aux;
			Cell *parent = current->parent;
			if(parent != NULL)
				search_result.path_cost += sqrt((pow(current->x - parent->x, 2) + pow(current->y - parent->y, 2)));

			current = current->parent;
		}

		search_result = reverse_search_result_path(search_result);
	}

	int i;
	for(i = 0; i < search_result.expanded_nodes; i++)
		free(expanded_cells_array[i]);

	free(expanded_cells_array);
	deque_destroy(expand);
	return search_result;
 }


SearchResultData depth_first_search(Maze *m, Cell start, Cell end){
	SearchResultData search_result = search_result_data_create();

	int neighbours[8][2] = {{-1,0}, {-1, 1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0, -1}, {-1,-1}};

	Cell *cell = cell_construct(start.x, start.y, NULL);
	Deque *expand = deque_construct();
	deque_push_front(expand, cell);

	int allocated_size = 40;
	Cell **expanded_cells_array = calloc(allocated_size, sizeof(Cell*));

	while(deque_size(expand)){
		cell = deque_pop_front(expand);
		maze_set_cell(m, cell->x, cell->y, EXPANDED);
		search_result.expanded_nodes++;

		if(allocated_size <= search_result.expanded_nodes){
			allocated_size *= 2;
			expanded_cells_array = realloc(expanded_cells_array, allocated_size * sizeof(Cell*));
		}

		expanded_cells_array[search_result.expanded_nodes - 1] = cell;

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
			deque_push_front(expand, new_cell);
			maze_set_cell(m, new_cell->x, new_cell->y, FRONTIER);
		}
	}

	if(search_result.sucess){
		Cell *current = cell;
		int allocated = search_result.expanded_nodes / 4;
		search_result.path = calloc(allocated, sizeof(Cell));

		while(current != NULL){
			if(search_result.path_length >= allocated){
				allocated *= 2;
				search_result.path = realloc(search_result.path, allocated * sizeof(Cell));
			}

			Cell aux = {current->x, current->y, NULL};
			search_result.path[search_result.path_length++] = aux;
			Cell *parent = current->parent;
			if(parent != NULL)
				search_result.path_cost += sqrt((pow(current->x - parent->x, 2) + pow(current->y - parent->y, 2)));

			current = current->parent;
		}

		search_result = reverse_search_result_path(search_result);
	}

	int i;
	for(i = 0; i < search_result.expanded_nodes; i++)
		free(expanded_cells_array[i]);

	free(expanded_cells_array);
	deque_destroy(expand);
	return search_result;
 }


//SearchResultData depth_first_search(Maze *m, Cell start, Cell end){
//	SearchResultData search_result = search_result_data_create();
//
//	int neighbours[8][2] = {{-1,0}, {-1, 1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0, -1}, {-1,-1}};
//
//	Cell *cell = cell_construct(start.x, start.y, NULL);
//	Stack *adjacent_list = stack_construct();
//	stack_push(adjacent_list, cell);
//
//	int allocated_size = 40;
//	Cell **frontier_cells = calloc(allocated_size, sizeof(Cell*));
//	int count = 0;
//	frontier_cells[count++] = cell;
//
//	while(!stack_empty(adjacent_list)){
//		cell = stack_pop(adjacent_list);
//		maze_set_cell(m, cell->x, cell->y, EXPANDED);
//		search_result.expanded_nodes++;
//
//		if(cell_is_equal(*cell, end)){
//			search_result.sucess = 1;
//			break;
//		}
//
//		int i;
//		for(i = 0; i < 8; i++){
//			int x = neighbours[i][0] + cell->x;
//			int y = neighbours[i][1] + cell->y;
//
//			if(x < 0 || x >= maze_return_rows(m) || y < 0 || y >= maze_return_cols(m))
//				continue;
//
//			int verify = maze_get_cell(m, x, y);
//			if(verify == OCCUPIED || verify == EXPANDED || verify == FRONTIER)
//				continue;
//
//			Cell *new_cell = cell_construct(x, y, cell);
//			stack_push(adjacent_list, new_cell);
//			maze_set_cell(m, new_cell->x, new_cell->y, FRONTIER);
//
//			if(allocated_size <= count){
//				allocated_size *= 2;
//				frontier_cells = realloc(frontier_cells, allocated_size * sizeof(Cell*));
//			}
//
//			frontier_cells[count++] = new_cell;
//		}
//	}
//
//	if(search_result.sucess){
//		Cell *current = cell;
//		int allocated = search_result.expanded_nodes / 4;
//		search_result.path = calloc(allocated, sizeof(Cell));
//
//		while(current != NULL){
//			if(search_result.path_length >= allocated){
//				allocated *= 2;
//				search_result.path = realloc(search_result.path, allocated * sizeof(Cell));
//			}
//
//			Cell aux = {current->x, current->y};
//			search_result.path[search_result.path_length++] = aux;
//			Cell *parent = current->parent;
//			if(parent != NULL)
//				search_result.path_cost += sqrt((pow(current->x - parent->x, 2) + pow(current->y - parent->y, 2)));
//
//			current = current->parent;
//		}
//	}
//
//	search_result = reverse_search_result_path(search_result);
//
//	int i;
//	for(i = 0; i < count; i++)
//		free(frontier_cells[i]);
//
//	free(frontier_cells);
//	stack_destroy(adjacent_list);
//	return search_result;
// }
