// contains command definitions

#include <stdio.h>
#include "character.h"
#include "area.h"
#include "cmd.h"

// move monster or player
void move_mon(struct Character* ptr_mon, struct Area* ptr_grid, enum Direction dir)
{
	int x = *ptr_mon->pos.x;
	int y = *ptr_mon->pos.y;

	ptr_grid->tile[x][y].mon = NULL;

	switch (dir)
	{	case north:
			*ptr_mon->pos.y = *ptr_mon->pos.y - 1;
			y -= 1;
			break;
		case south:
			*ptr_mon->pos.y = *ptr_mon->pos.y + 1;
			y += 1;
			break;
		case east:
			*ptr_mon->pos.x = *ptr_mon->pos.x + 1;
			x += 1;
			break;
		case west:
			*ptr_mon->pos.x = *ptr_mon->pos.x - 1;
			x -= 1;
			break;
		default:
			break;
	}

	ptr_grid->tile[x][y].mon = ptr_mon;
}

