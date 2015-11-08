// main file for YET TO BE NAMED GAME

#include <stdio.h>
#include <ncurses.h>
#include "character.h"

int main()
{
	initscr();
	clear();

	// declare player character as type Character
	struct Character* player;

	player = init_character();

//	player.name = "Ben";
//	player.pos->x = 0;
//	player.pos->y = 0;
	
	printw("%s at (%d,%d)\n", player->name, *player->pos.x, *player->pos.y);

	refresh();

	endwin();	

	clean_character(player);

	return 0;
}


