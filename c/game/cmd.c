// contains command definitions

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "character.h"
#include "area.h"
#include "cmd.h"


struct Game_cmd* get_cmd()
{
	struct Game_cmd* temp = malloc(sizeof(struct Game_cmd));
	noecho();
	cbreak();
	//echo();
	temp->input = getch();
	echo();
	temp->cmd = which_cmd(temp->input);

	return temp;
}

enum cmd_code which_cmd(char command)
{
	if (command == 'q')
	{
		return CMD_QUIT;
	}
	else
	{
		return CMD_WAIT;
	}
}

// inits game command ptr and returns to calling function
struct Game_cmd* init_game_cmd(struct Character* ptr_mon)
{
	struct Game_cmd* temp_cmd;

	temp_cmd = malloc(sizeof(struct Game_cmd));

	temp_cmd->mon = ptr_mon;

	temp_cmd->cmd = CMD_WAIT;

	temp_cmd->input = '\0';
	return temp_cmd;
}
/*
void process_cmd(struct Game_cmd* ptr_cmd)
{
	if (ptr_cmd->cmd == CMD_MOVE)
	{
		if (ptr_cmd->input == '8')
			move_mon(ptr_cmd->mon, 	
*/
void clean_game_cmd(struct Game_cmd* ptr_game_cmd)
{
	free(ptr_game_cmd);
}

// move monster or player
void move_mon(struct Character* ptr_mon, struct Area* ptr_grid, enum Direction dir)
{
	int x = *ptr_mon->pos.x;
	int y = *ptr_mon->pos.y;

	ptr_grid->tile[x][y].mon = NULL;

	switch (dir)
	{	case north:
			*ptr_mon->pos.y = *ptr_mon->pos.y + 1;
			y += 1;
			break;
		case south:
			*ptr_mon->pos.y = *ptr_mon->pos.y - 1;
			y -= 1;
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

