// contains area definitions and COORDINATE SYSTEM info
#include <stdio.h>

#ifndef AREA_H
#define AREA_H


#define GRIDMAX 20

// coordinate contains the (x,y) location for a cartesian plane
struct Coordinate 
{
	int* x, * y;
};

// enum for direction --> may move to a different file
enum Direction
{
	north,
	south,
	east,
	west
};
// floore tile that contains up to one enemy/player, and multiple items
struct Tile
{
	char floor[2];// = { '.', '#' };	
};

// map made up of multiple tiles
struct Area
{
	struct Tile** tile;
};

struct Area* init_grid();

void print_grid(struct Area* ptr_grid);

void clean_grid(struct Area* ptr_grid);


#endif //end AREA_H
