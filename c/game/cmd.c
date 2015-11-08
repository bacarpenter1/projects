// contains command definitions

#include <stdio.h>
#include "cmd.h"

// move monster or player
void move_mon(struct Character mon, enum Direction dir)
{
	switch (dir)
		case north:
			mon.pos->y = mon.pos->y + 1;
			break;
		case south:
			mon.pos->y = mon.pos->y - 1;
			break;
		case east:
			mon.pos->x = mon.pos->x - 1;
			break;
		case west:
			mon.pos->x = mon.pos->x +1;
			break;
		default:
			break;

}

