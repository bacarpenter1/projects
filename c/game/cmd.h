#include <stdio.h>
#include <stdlib.h>

#ifndef CMD_H
#define CMD_H
#include "character.h"
#include "area.h"

enum cmd_code
{
	CMD_WAIT,
	CMD_MOVE,
	CMD_QUIT
};	

enum Direction
{
	north = 8,
	south = 2,
	east = 6,
	west = 4
};

struct command
{
	enum cmd_code code;
	enum Direction;
};

struct Game_cmd
{
	char input;
	enum cmd_code cmd;
	struct Character* mon;
};


struct Game_cmd* get_cmd();

enum cmd_code which_cmd(char command);

struct Game_cmd* init_game_cmd(struct Character* ptr_mon);

void process_cmd(struct Game_cmd* ptr_cmd);

void clean_game_cmd(struct Game_cmd* ptr_game_cmd);

typedef void (*cmd_handler_fn)(struct Character* mon, struct Game_cmd* command);

void move_mon(struct Character* ptr_mon, struct Area* ptr_grid, enum Direction dir);

#endif //CMD_H
