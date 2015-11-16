#include <stdio.h>
#include <ncurses.h>

#include "screen.h"
#include "character.h"
#include "area.h"
#include "coordinate.h"

void update_screen(struct Character* ptr_player, struct Area* ptr_grid)
{
	int offset = 0;
	clear();

	printw("\n");
	print_location(ptr_player);
	print_grid(ptr_grid);

	if (ptr_player->target != NULL)
	{
		print_location(ptr_player->target);
//		offset = 2;
	}

//	move(GRIDMAX_Y + 1 + offset - *ptr_player->pos.y, *ptr_player->pos.x);
	move(0,0);
	
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!refresh() is called in main.c!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//	refresh();
}
