#include <stdio.h>
#include <ncurses.h>

#include "screen.h"
#include "character.h"
#include "area.h"
#include "coordinate.h"

void update_screen(struct Character* ptr_player, struct Area* ptr_grid)
{
	int offset = 0;
//	clear(); ->>>> CLEAR USED IN MAIN.C

	printw("\n");
	print_location(ptr_player);
	print_grid(ptr_grid);

	if (ptr_player->target != NULL)
	{
		print_location(ptr_player->target);
	}

	move(0,0);
	
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!refresh() is called in main.c!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//	refresh();
}
