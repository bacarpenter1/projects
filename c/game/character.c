#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "character.h"

// initialize several character traits
struct Character* init_character()
{
	// delcare and allocate mem for whole struct
	struct Character* mon = malloc(sizeof(struct Character));

	mon->name = "Ben";
	mon->sym = '@';
	mon->health = 10;
	mon->maxHealth = 10;
	mon->type = player;
	mon->target = NULL;

	// allocate mem for coordinates
	mon->pos.x = malloc(sizeof(int));
	mon->pos.y = malloc(sizeof(int));

	// initialize coordinates to 1,1 (not on a wall)
	*(mon->pos.x) = 1;
	*(mon->pos.y) = 1;

	return mon;
}

void clean_character(struct Character* mon)
{
	// free coordinates, then character
	free(mon->pos.x);
	free(mon->pos.y);

	free(mon);
}

// actually prints info
void print_location(struct Character* mon)
{
	printw("%s is at (%d,%d)\nHP: %d/%d\n", 
		mon->name, *mon->pos.x, *mon->pos.y, mon->health, mon->maxHealth);
}	
