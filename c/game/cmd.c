// contains command definitions

#include <stdio.h>
#include "cmd.h"

// move monster or player
void move_mon(struct Character* ptr_mon, enum Direction dir)
{
	switch (dir)
	{	case north:
			*ptr_mon->pos.y = *ptr_mon->pos.y + 1;
			break;
		case south:
			*ptr_mon->pos.y = *ptr_mon->pos.y - 1;
			break;
		case east:
			*ptr_mon->pos.x = *ptr_mon->pos.x - 1;
			break;
		case west:
			*ptr_mon->pos.x = *ptr_mon->pos.x +1;
			break;
		default:
			break;
	}
}

