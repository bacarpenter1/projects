#include <stdio.h>
#include <stdlib.h>
#include "coordinate.h"

void clean_coordinate(struct Coordinate* ptr_pair)
{
	free(ptr_pair->x);
	free(ptr_pair->y);

	return;
}
