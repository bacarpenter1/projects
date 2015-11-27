#include <stdio.h>

#ifndef COORDINATE_H
#define COORDINATE_H

struct Coordinate
{
	int *x, * y;
};

void clean_coordinate(struct Coordinate* ptr_pair);

#endif //COORDINATE_H
