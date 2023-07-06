#include <stdio.h>
#include <stdlib.h>
#include "source/maze.h"
#include "source/searchs.h"

void display_result(SearchResultData *search_result)
{
    if (!search_result->sucess)
    {
        printf("IMPOSSIBLE\n");
        return;
    }

    for (int i = 0; i < search_result->path_size; i++)
        printf("%d %d\n", search_result->path[i].x, search_result->path[i].y);

    printf("%.2lf\n", search_result->path_cost);
    printf("%d\n", search_result->path_size);
    printf("%d\n", search_result->expanded_nodes);
}

void show_entire_path(Maze *m, SearchResultData *search, Cell inicio, Cell fim)
{
    if (search->sucess)
    {
        for (int i = 0; i < search->path_size; i++)
        	maze_set_cell(m, search->path[i].x, search->path[i].y, PATH);
    }

    maze_set_cell(m, inicio.x, inicio.y, START);
    maze_set_cell(m, fim.x, fim.y, END);
    maze_display(m);
}

int main()
{
    char maze_file[100];
    char search[100];
    Cell start, end;
    SearchResultData search_result;
    Maze *lab;

    scanf("%s", maze_file);
    scanf("%d %d", &start.x, &start.y);
    scanf("%d %d", &end.x, &end.y);
    scanf("\n%s", search);

    lab = maze_load(maze_file);

    //search_result = dummy_search(lab, start, end);
    display_result(&search_result);
    show_entire_path(lab, &search_result, start, end);

    maze_destroy(lab);
    if (search_result.path != NULL)
        free(search_result.path);

    return 0;
}
