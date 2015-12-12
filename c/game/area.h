// contains area definitions and COORDINATE SYSTEM info
#include <stdio.h>

#ifndef AREA_H
#define AREA_H

#include "character.h"

#define GRIDMAX_X 80
#define GRIDMAX_Y 20

// coordinate contains the (x,y) location for a cartesian plane
/*	MOVED TO coordinate.h for modularity
struct Coordinate 
{
	int* x, * y;
};
*/

// enum for direction --> may move to a different file
// MOVED TO cmd.h
/*
enum Direction
{
	north,
	south,
	east,
	west
};
*/

enum tileType
{
	floor = 0,
	wall = 1,
	up_stair = 2,
	down_stair = 3,
	door_closed = 4,
	door_open = 5
};

// floore tile that contains up to one enemy/player, and multiple items
struct Tile
{
	char floor[2]; // = { '.', '#' };	
	enum tileType type;	
	struct Character* mon;
	struct Item* item;	
};

// map made up of multiple tiles
struct Area
{
	int level;
	struct Tile** tile;
};

struct Area* init_grid();

void add_to_grid(struct Character* ptr_mon, struct Area* ptr_grid);

void print_grid(struct Area* ptr_grid);

void update_grid(struct Area* ptr_grid);

void clean_grid(struct Area* ptr_grid);

void gen_level(struct Area* ptr_grid);

struct Character* find_player(struct Area* ptr_grid);
#endif //end AREA_H
