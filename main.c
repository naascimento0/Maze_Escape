#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "source/maze.h"
#include "source/searchs.h"

void display_result(SearchResultData *search_result)
{
    if (!search_result->sucess)
    {
        printf("IMPOSSIBLE\n");
        return;
    }

    for (int i = 0; i < search_result->path_length; i++)
        printf("%d %d\n", search_result->path[i].x, search_result->path[i].y);

    printf("%.2lf\n", search_result->path_cost);
    printf("%d\n", search_result->path_length);
    printf("%d\n", search_result->expanded_nodes);
}

void show_entire_path(Maze *m, SearchResultData *search, Cell end, Cell start)
{
    if (search->sucess)
    {
        for (int i = 0; i < search->path_length; i++)
        	maze_set_cell(m, search->path[i].y, search->path[i].x, PATH);
    }

    maze_set_cell(m, start.y, start.x, START);
    maze_set_cell(m, end.y, end.x, END);
    maze_display(m);
}

int main()
{
    char maze_file[100];
    char algorithm[100];
    Cell start, end;
    SearchResultData search_result;
    Maze *maze;

    scanf("%s", maze_file);
    scanf("%d %d", &start.x, &start.y);
    scanf("%d %d", &end.x, &end.y);
    scanf("\n%s", algorithm);

    maze = maze_load(maze_file);

    if (!strcmp(algorithm, "BFS"))
    	search_result = breadth_first_search(maze, start, end);
//    else if (!strcmp(algorithm, "DFS"))
//    	search_result = depth_first_search(maze, start, end);
//    else if (!strcmp(algorithm, "A*"))
//    	search_result = a_star(maze, start, end);
    else
    {
        printf("Unknown Algorithm: %s\n", algorithm);
        exit(1);
    }

    printf("\n");
    maze_display(maze);
    printf("\nRESULT:\n");
    display_result(&search_result);
    show_entire_path(maze, &search_result, start, end);

    maze_destroy(maze);
    if (search_result.path != NULL)
        free(search_result.path);

    return 0;
}
