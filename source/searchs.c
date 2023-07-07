#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "searchs.h"
#include "source/data_structures/deque.h"

SearchResultData search_result_data_create(){
	SearchResultData search_result;
	search_result.path = NULL;
	search_result.path_cost = 0;
	search_result.path_size = 0;
	search_result.expanded_nodes = 0;
	search_result.sucess = 0;
    return search_result;
}

// SearchResult a_star_search(Maze *m, Cell start, Cell end){
//     SearchResult sr;
//     // TODO!
//     return sr;
// }

SearchResultData breadth_first_search(Maze *m, Cell start, Cell end){
	SearchResultData search_result = search_result_data_create();

	int visited[maze_return_rows(m)][maze_return_cols(m)];

	int neighbours[8][2] = {{-1,-1}, {-1,0} ,{-1, 1}, {0,-1}, {0,0}, {0,1}, {1,1}, {1,0	}, {1,1}};

	Deque *expand = deque_construct();
	deque_push_back(expand, &start);

	while(deque_size){
		Cell *cell = deque_pop_back(expand);
		maze_set_cell(m, cell->x, cell->y, EXPANDED);

		int i;
		for(i = 0; i < 8; i++){
			int x = neighbours[i][0] + cell->x;
			int y = neighbours[i][1] + cell->y;

			if(x < 0 || x >= maze_return_rows(m) || y < 0 || maze_return_cols(m))
				continue;
			
			int verify = maze_get_cell(m, x, y);
			if(verify == OCCUPIED || verify == EXPANDED || verify == FRONTIER)
				continue;
			
			Cell new_cel;
			new_cel.x = x;
			new_cel.y = y;
			deque_push_back(expand, &new_cel);
		}




		
	}
	

     return search_result;
 }

// SearchResult depth_first_search(Maze *m, Cell start, Cell end){
//     SearchResult sr;
//     // TODO!
//     return sr;
// }
