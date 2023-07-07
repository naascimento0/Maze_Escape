#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "searchs.h"

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
	SearchResultData search_result;



     return search_result;
 }

// SearchResult depth_first_search(Maze *m, Cell start, Cell end){
//     SearchResult sr;
//     // TODO!
//     return sr;
// }
