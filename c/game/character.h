#include <stdio.h>
#include <stdlib.h>

#ifndef CHARACTER_H
#define CHARACTER_H
#include "item.h"
#include "area.h"

struct Character
{
	char* name;
	struct Item inventory[10];
	struct Coordinate pos;
};// Character;

struct  Character* init_character();

void clean_character(struct Character* mon);

void print_location(struct Character* mon);
	
#endif //CHARACTER_H		
