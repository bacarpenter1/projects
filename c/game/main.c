// main file for YET TO BE NAMED GAME

#include <stdio.h>
#include <ncurses.h>
#include "character.h"
#include "cmd.h"
#include "area.h"

int main()
{
	initscr();
	clear();

	// declare player character as type Character
	struct Character* player;
	struct Area* grid;

	player = init_character();
	grid = init_grid();

//	player.name = "Ben";
//	player.pos->x = 0;
//	player.pos->y = 0;
	
//	printw("%s at (%d,%d)\n", player->name, *player->pos.x, *player->pos.y);
	print_location(player);
	move_mon(player, north);
	print_location(player);

	print_grid(grid);

	refresh();

	endwin();	

	clean_character(player);
	clean_grid(grid);
	return 0;
}


