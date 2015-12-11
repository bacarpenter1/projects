#include <stdio.h>
#include <stdlib.h>

#ifndef CMD_H
#define CMD_H
#include "character.h"
#include "area.h"

#define INVWIN_XWIDTH 40
#define INVWIN_XPOS 40
#define INVWIN_YPOS 0

enum cmd_code
{
	CMD_WAIT,
	CMD_MOVE,
	CMD_OPEN,
	CMD_CLOSE,
	CMD_DOWN,
	CMD_UP,
	CMD_INV,
	CMD_QUIT
};	

enum Direction
{
	none = 0,
	self = 5,
	north = 8,
	south = 2,
	east = 6,
	west = 4,
	seast = 3,
	swest = 1,
	nwest = 7,
	neast = 9
};

struct Command
{
	char input;
	enum cmd_code code;
	enum Direction dir;
	struct Character* mon;
};


typedef void (*cmd_handler_fn)(struct Command* ptr_cmd, struct Area* ptr_grid);

struct Game_cmd
{
//	char input;
	enum cmd_code cmd;
//	enum Direction dir;
//	struct Character* mon;
	cmd_handler_fn fn;
	
};


struct Command* get_cmd();

enum cmd_code which_cmd(char command);

enum Direction proc_direction(struct Command* ptr_cmd);

struct Command* init_game_cmd(struct Character* ptr_mon);

void process_cmd(struct Command* ptr_cmd);

void exec_cmd(struct Command* ptr_cmd, struct Area* grid);

void clean_game_cmd(struct Command* ptr_game_cmd);

void attack(struct Character* ptr_attacker, struct Character* ptr_defender);
//void move_mon(struct Character* ptr_mon, struct Area* ptr_grid, enum Direction dir);
void move_mon(struct Command* ptr_cmd, struct Area* ptr_grid);

void open(struct Command* ptr_cmd, struct Area* ptr_grid);

void close(struct Command* ptr_cmd, struct Area* ptr_grid);

void wait_cmd(struct Command* ptr_cmd, struct Area* ptr_grid);

void go_down(struct Command* ptr_cmd, struct Area* ptr_grid);

void go_up(struct Command* ptr_cmd, struct Area* ptr_grid);

void list_inventory(struct Command* ptr_cmd, struct Area* ptr_grid);

struct Coordinate* new_location(int x, int y, enum Direction dir);

enum Direction arrow_keys(char direction);
#endif //CMD_H
