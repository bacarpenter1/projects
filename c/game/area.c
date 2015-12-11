// init grid, print grid functions

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "area.h"
#include "coordinate.h"
#include "character.h"

// all characters for tile type
const char tile_character[] = { '.', '#', '<', '>', '+', ','};

//grid init
struct Area* init_grid(struct Character* ptr_player)
{	
	// malloc for the grid ptr
	struct Area* ptr_grid = malloc(sizeof(struct Area));

	// used for wall generation
	int randx = 0;
	int randy = 0;

	// genearte wall positions
	randx = rand() % 40 + 20;
	randy = rand() % 15 + 5;

	// malloc for each tile in grid, and init for each tile
	ptr_grid->tile = malloc(sizeof(struct Tile*) * GRIDMAX_X);
	for (int i = 0; i < GRIDMAX_X; i++)
	{
		ptr_grid->tile[i] = malloc(sizeof(struct Tile) * GRIDMAX_Y);
		for (int j = 0; j < GRIDMAX_Y; j++)
		{
			ptr_grid->tile[i][j].mon = NULL;
			ptr_grid->tile[i][j].type = wall;
		}
	}

	// ititialize level number
	ptr_grid->level = 0;
//	ptr_grid->tile[0][0].mon = ptr_player;

	return ptr_grid;
}

// add a character to the grid
void add_to_grid(struct Character* ptr_mon, struct Area* ptr_grid)
{
	// add them in a random spot
	int randx, randy;

	// ensure they don't land on a door or wall
	do
	{	
		randx = rand() % (GRIDMAX_X - 4) + 2;
		randy = rand() % (GRIDMAX_Y - 4) + 2;
	} while (ptr_grid->tile[randx][randy].type != floor && 
			ptr_grid->tile[randx][randy].mon != NULL);

	// assign position to character struct
	*ptr_mon->pos.x = randx;
	*ptr_mon->pos.y = randy;

	// place character on the tile
	ptr_grid->tile[randx][randy].mon = ptr_mon;
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
			// if there's a monster, print it otherwise print the tile
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
			/*	//some debug stufff
				else
				{
					*ptr_grid->tile[i][j].mon->pos.x = i;
					*ptr_grid->tile[i][j].mon->pos.y = j;
					
				}*/
			}
		//	printw("^");
		}
		//printw("\n");
	}
}
//generate the level layout 		
void gen_level(struct Area* ptr_grid)
{
	// variables for wall positions	
	int randx = 0;
	int randy = 0;
	int randsubx = 0;
	int randsuby = 0;
	int notempty = 1;
	int in_wall = 1;

	struct Character* ptr_player;

	ptr_player = find_player(ptr_grid);
	// make sure rooms arent too small
	do
	{
		randx = rand() % 40 + 20;
		randy = rand() % 15 + 4;

		// check player position
		if (ptr_player != NULL)
		{
			if (*ptr_player->pos.x != randx)
			{
				in_wall = 0;
		
			}
		
		}
		else
		{
			in_wall = 0;
		}

	} while (in_wall);
	
	in_wall = 1;
	
 	do
	{	
		randsubx = rand() % (randx - 15) + 2;
		randsuby = rand() % (randy - 3) + 3;

		if (ptr_player != NULL)
		{
			if (*ptr_player->pos.y != randsuby)
			{
				in_wall = 0;
			}
		}
		else
		{
			in_wall = 0;
		}

	} while (in_wall);

	
	// place walls and doors on tiles
	for (int i = 0; i < GRIDMAX_X; i++)
	{
		for (int j = 0; j < GRIDMAX_Y; j++)
		{
			ptr_grid->tile[i][j].mon = NULL;

			if (i == 0 || j == 0 || j == GRIDMAX_Y - 1 || i == GRIDMAX_X -1 
				|| i == randx)
			{
				ptr_grid->tile[i][j].type = wall;
	
				if (i == randx && j == randy)
				{
					ptr_grid->tile[i][j].type = door_closed;
				}
			}
			else if (j == randsuby && i < randx)
			{
				ptr_grid->tile[i][j].type = wall;

				if (i == randsubx)
				{
					ptr_grid->tile[i][j].type = door_closed;
				}
			}
			else
			{

				ptr_grid->tile[i][j].type = floor;
			}
		}
	}
	
	// randomly place a down stair
	do
	{	
		randx = rand() % (GRIDMAX_X - 1) + 1;
		randy = rand() % (GRIDMAX_Y - 1) + 1;
	} while (ptr_grid->tile[randx][randy].type != floor); 

	ptr_grid->tile[randx][randy].type = down_stair;

	// update the grid
	update_grid(ptr_grid);
}

struct Character* find_player(struct Area* ptr_grid)
{
	struct Character* ptr_character = NULL;	

	for (int i = 0; i < GRIDMAX_X; i++)
	{
		for (int j = 0; j < GRIDMAX_Y; j++)
		{
			if (ptr_grid->tile[i][j].mon != NULL)
			{
				
				if (ptr_grid->tile[i][j].mon->type == player)
				{
					ptr_character = ptr_grid->tile[i][j].mon;
//					clear();
/*					printw("Found");
					refresh();
					getch();
				
*/				}
			}
		}
	}

	return ptr_character;
}
