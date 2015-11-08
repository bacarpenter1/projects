// contains area definitions and COORDINATE SYSTEM info
#include <stdio.h>

#ifndef AREA_H
#define AREA_H

// coordinate contains the (x,y) location for a cartesian plane
struct Coordinate 
{
	int* x, * y;
};

// enum for direction
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
	
};

// map made up of multiple tiles
struct Area
{
};

#endif //end AREA_H
