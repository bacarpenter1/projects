#include <stdio.h>
#include <stdlib.h>

#ifndef CMD_H
#define CMD_H
#include "character.h"

void move_mon(struct Character* ptr_mon, struct Area* ptr_grid, enum Direction dir);

#endif //CMD_H
