#include <stdio.h>

#ifndef SCREEN_H
#define SCREEN_H

#include "cmd.h"
#include "area.h"
#include "character.h"
#include "coordinate.h"

void update_screen(struct Character* ptr_player, struct Area* ptr_grid);

#endif //SCREEN_H
