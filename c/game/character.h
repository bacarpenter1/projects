#include <stdio.h>
#include <stdlib.h>

#ifndef CHARACTER_H
#define CHARACTER_H
#include "item.h"
//#include "area.h"
#include "coordinate.h"

enum CharacterType
{
	player,
	monster
};
struct Character
{
	char* name;
	char sym;
	int health, maxHealth;
	struct Item inventory[10];
	struct Coordinate pos;
	enum CharacterType type;
	struct Character* target;
};// Character;

struct  Character* init_character();

void clean_character(struct Character* mon);

void print_location(struct Character* mon);
	
#endif //CHARACTER_H		
