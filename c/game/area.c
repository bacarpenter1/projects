// init grid, print grid functions

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "area.h"
#include "coordinate.h"
#include "character.h"

//grid init
struct Area* init_grid(struct Character* ptr_player)
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

	ptr_grid->tile[0][0].mon = ptr_player;

	return ptr_grid;
}

void add_to_grid(struct Character* ptr_mon, struct Area* ptr_grid)
{
	*ptr_mon->pos.x = 5;
	*ptr_mon->pos.y = 5;
	ptr_grid->tile[5][5].mon = ptr_mon;
}	

//print grid
void print_grid(struct Area* ptr_grid)
{
	// print for typical cartesian grid
	for (int j = GRIDMAX-1 ; j >= 0; j-- )
	{
		for (int i = 0; i < GRIDMAX; i++)
		{
			// print each tile!
			if (ptr_grid->tile[i][j].mon != NULL)
			{
				printw("%c", ptr_grid->tile[i][j].mon->sym);
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


// update_grid after each cmd, using monster position
void update_grid(struct Area* ptr_grid)
{
	int x, y;

	for (int i = 0; i < GRIDMAX; i++)
	{
		for (int j = 0; j < GRIDMAX; j++)
		{
			if (ptr_grid->tile[i][j].mon != NULL)
			{
		//		printw("$");
				x = *ptr_grid->tile[i][j].mon->pos.x;
				y = *ptr_grid->tile[i][j].mon->pos.y;  
				
				if ( ((x != i) || (y != j)) && ptr_grid->tile[x][y].mon == NULL )
				{
					ptr_grid->tile[x][y].mon = ptr_grid->tile[i][j].mon;
					ptr_grid->tile[i][j].mon = NULL;
				}
				else
				{
					*ptr_grid->tile[i][j].mon->pos.x = i;
					*ptr_grid->tile[i][j].mon->pos.y = j;
					
				}
			}
		//	printw("^");
		}
		//printw("\n");
	}
}
			
