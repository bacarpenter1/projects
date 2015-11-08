#include <stdio.h>
#include <stdlib.h>
#include "character.h"

// initialize several character traits
struct Character* init_character()
{
	// delcare and allocate mem for whole struct
	struct Character* mon = malloc(sizeof(struct Character));

	mon->name = "Ben";
	// allocate mem for coordinates
	mon->pos.x = malloc(sizeof(int));
	mon->pos.y = malloc(sizeof(int));

	// initialize coordinates to 0,0
	*(mon->pos.x) = 0;
	*(mon->pos.y) = 0;

	return mon;
}

void clean_character(struct Character* mon)
{
	// free coordinates, then character
	free(mon->pos.x);
	free(mon->pos.y);

	free(mon);
}
