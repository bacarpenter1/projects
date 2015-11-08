// init grid, print grid functions

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "area.h"

//grid init
struct Area* init_grid()
{	
	// malloc for the grid ptr
	struct Area* ptr_grid = malloc(sizeof(struct Area));

	// malloc for each tile in grid, and init for each tile
	ptr_grid->tile = malloc(sizeof(struct Tile*) * GRIDMAX);
	for (int i = 0; i < GRIDMAX; i++)
	{
		ptr_grid->tile[i] = malloc(sizeof(struct Tile) * GRIDMAX);
		for (int j = 0; j < GRIDMAX; j++)
		{
			ptr_grid->tile[i][j].mon = NULL;
		}
	}

	return ptr_grid;
}

//print grid
void print_grid(struct Area* ptr_grid)
{
	for (int j = 0; j < GRIDMAX; j++ )
	{
		for (int i = 0; i < GRIDMAX; i++)
		{
			// print each tile!
			if (ptr_grid->tile[i][j].mon != NULL)
			{
				printw("@");
			}
			else
			{ 
				printw(".");//, *ptr_grid->tile[i][j].floor[0];
			}
		}
		printw("\n");
	}
}

// free all grid memory
void clean_grid(struct Area* ptr_grid)
{
	for (int i = 0; i < GRIDMAX; i++)
	{
		free(ptr_grid->tile[i]);
	}

	free(ptr_grid->tile);
	free(ptr_grid);
}

	
