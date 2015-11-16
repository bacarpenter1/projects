// init grid, print grid functions

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "area.h"
#include "coordinate.h"
#include "character.h"

const char tile_character[] = { '.', '#', '<', '>', '+', ','};

//grid init
struct Area* init_grid(struct Character* ptr_player)
{	
	// malloc for the grid ptr
	struct Area* ptr_grid = malloc(sizeof(struct Area));

	// malloc for each tile in grid, and init for each tile
	ptr_grid->tile = malloc(sizeof(struct Tile*) * GRIDMAX_X);
	for (int i = 0; i < GRIDMAX_X; i++)
	{
		ptr_grid->tile[i] = malloc(sizeof(struct Tile) * GRIDMAX_Y);
		for (int j = 0; j < GRIDMAX_Y; j++)
		{
			ptr_grid->tile[i][j].mon = NULL;

			if (i == 0 || j == 0 || j == GRIDMAX_Y - 1 || i == GRIDMAX_X -1 || i == 20)
			{
				ptr_grid->tile[i][j].type = wall;
				if (i == 20 && j == 10)
				{
					ptr_grid->tile[i][j].type = door_closed;
				}
			}
			else if (i == 20 && j == 10)
			{
				ptr_grid->tile[i][j].type = door_closed;
			}
			else
			{

				ptr_grid->tile[i][j].type = floor;
			}
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
	int player_x = 0, player_y = 0;
	// print for typical cartesian grid
	for (int j = GRIDMAX_Y-1 ; j >= 0; j-- )
	{
		for (int i = 0; i < GRIDMAX_X; i++)
		{
			// print each tile!
			if (ptr_grid->tile[i][j].mon != NULL)
			{
				printw("%c", ptr_grid->tile[i][j].mon->sym);
				if (ptr_grid->tile[i][j].mon->type == player)
				{
					player_x = i;
					player_y = j;
				}
			}
			else
			{ 
				printw("%c", tile_character[ptr_grid->tile[i][j].type]);
			}
		}
		printw("\n");
	}

}

// free all grid memory
void clean_grid(struct Area* ptr_grid)
{
	for (int i = 0; i < GRIDMAX_X; i++)
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

	for (int j = 0; j < GRIDMAX_Y; j++)
	{
		for (int i = 0; i < GRIDMAX_X; i++)
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
				else if (ptr_grid->tile[i][j].mon->health <= 0)
				{
					*ptr_grid->tile[i][j].mon->pos.x = 0;
					*ptr_grid->tile[i][j].mon->pos.y = 0;
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
			
