// contains command definitions

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "character.h"
#include "area.h"
#include "cmd.h"


struct Command* get_cmd()
{
	struct Command* temp = malloc(sizeof(struct Command));
	noecho();
	cbreak();
	//echo();
	temp->input = getch();
	if (temp->input == '\033')
	{
//		getch(); //skip [
		proc_direction(temp);
	}
	echo();
	temp->code = which_cmd(temp->input);

	return temp;
}

#define NUM_CMDS 4
const struct Game_cmd cmd_list[] = 
{
	//cmd_code, dir, Character*, handler_fn
	{ CMD_WAIT, wait_cmd},
	{ CMD_MOVE, move_mon},
	{ CMD_OPEN, open},
	{ CMD_CLOSE, close}
};

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

enum Direction proc_direction(struct Command* ptr_cmd)
{
	noecho();
	char direction;
	if (ptr_cmd->input > '0' &&  ptr_cmd->input < '9')
	{ 
		ptr_cmd->dir = ptr_cmd->input -48;
	}
	else if (ptr_cmd->input == '\033')
	{
	//	direction = arrow_keys(direction);

/*		getch();
		direction = getch();
		
		switch (direction)
		{
			case 'A':
				direction = north;
				break;
			case 'B': 
				direction = south;
				break;
			case 'C':
				direction = east;
				break;
			case 'D':
				direction = west;
				break;
		}
*/
		ptr_cmd->dir = arrow_keys(direction);
	}
	else if (ptr_cmd->input == 'o' || ptr_cmd->input == 'c')
	{
		printw("Enter direction: ");
		direction = getch();
	
		if (direction > '0' && direction <= '9')
		{
			ptr_cmd->dir = direction - 48;
		}
		else
		{
			ptr_cmd->dir = arrow_keys(direction);
		}
	}
	

	return ptr_cmd->dir;
}

// inits game command ptr and returns to calling function
struct Command * init_game_cmd(struct Character* ptr_mon)
{
	struct Command* temp_cmd;

	temp_cmd = malloc(sizeof(struct Command));

	temp_cmd->mon = ptr_mon;

	temp_cmd->code = CMD_WAIT;

	temp_cmd->dir = none;

	temp_cmd->input = '\0';
	return temp_cmd;
}

// assign command code
void process_cmd(struct Command* ptr_cmd)
{
	//struct Command* ptr_exec_cmd = malloc(sizeof(struct Command));

	//ptr_exec_cmd->cmd_code = which_cmd(ptr_cmd->input);

	ptr_cmd->input = getch();
	ptr_cmd->dir = none;
//	proc_direction(ptr_cmd);

	if ( (ptr_cmd->input > 48 && ptr_cmd->input < 58 ) || 
		( ptr_cmd->input =='\033' ) )
	{
		ptr_cmd->code = cmd_list[1].cmd;
	}
	else if (ptr_cmd->input == 'o')
	{
		ptr_cmd->code = cmd_list[2].cmd;
	}
	else if (ptr_cmd->input == 'c')
	{
		ptr_cmd->code = cmd_list[3].cmd;
	}
	else
	{
		ptr_cmd->code = CMD_WAIT;
	}
}
// execute command
void exec_cmd(struct Command* ptr_cmd, struct Area* ptr_grid)
{

	for (int i = 0; i < NUM_CMDS /*&& ptr_cmd->code != cmd_list[i].cmd */; i++)
	{	
		// iff game codes match, execute
		if (ptr_cmd->code == cmd_list[i].cmd)
		{
			cmd_list[i].fn(ptr_cmd, ptr_grid);
			return;
		}
	}
}
void clean_game_cmd(struct Command* ptr_game_cmd)
{
	free(ptr_game_cmd);
}

// move monster or player

//void move_mon(struct Character* ptr_mon, struct Area* ptr_grid, enum Direction dir)
void move_mon(struct Command* ptr_cmd, struct Area* ptr_grid)
{
	proc_direction(ptr_cmd);

	int x = *ptr_cmd->mon->pos.x;
	int y = *ptr_cmd->mon->pos.y;

	ptr_grid->tile[x][y].mon = NULL;

	switch (ptr_cmd->dir)
	{	case north:
			if ((y+1) < GRIDMAX_Y)
			{
				y += 1;
			}
			break;
		case south:
			if ((y-1) >= 0)
			{
				y -= 1;
			}
			break;
		case east:
			if ((x+1) < GRIDMAX_X)
			{
				x += 1;
			}
			break;
		case west:
			if ((x-1) >= 0)
			{
				x -= 1;
			}
			break;
		default:
			break;
	}

	if (ptr_grid->tile[x][y].mon == NULL &&	ptr_grid->tile[x][y].type != wall
		&& ptr_grid->tile[x][y].type != door_closed)
	{	ptr_grid->tile[x][y].mon = ptr_cmd->mon;
		*ptr_cmd->mon->pos.x = x;
		*ptr_cmd->mon->pos.y = y;	
	}
	else if (ptr_grid->tile[x][y].type == door_closed)
	{
		open(ptr_cmd, ptr_grid);
	}
	else
	{
		if (ptr_grid->tile[x][y].mon != NULL)
		{
			attack(ptr_cmd->mon, ptr_grid->tile[x][y].mon);
/*			if (ptr_grid->tile[x][y].mon->health <= 0)
			{
				printw("you have killed it\n");
				ptr_grid->tile[x][y].mon = NULL;
			}
*/
		}
		x = *ptr_cmd->mon->pos.x;
		y = *ptr_cmd->mon->pos.y;

		ptr_grid->tile[x][y].mon = ptr_cmd->mon;
	}

	
}

void attack(struct Character* ptr_attacker, struct Character* ptr_defender)
{
	ptr_attacker->target = ptr_defender;
	ptr_defender->health--;

	if (ptr_defender->health <= 0)
	{
		ptr_attacker->target = NULL;
	}
}

void open(struct Command* ptr_cmd, struct Area* ptr_grid)
{
	int x, y;

	proc_direction(ptr_cmd);

	x = *ptr_cmd->mon->pos.x;
	y = *ptr_cmd->mon->pos.y;

	switch (ptr_cmd->dir)
	{	case north:
			if ((y+1) < GRIDMAX_Y)
			{
				y += 1;
			}
			break;
		case south:
			if ((y-1) >= 0)
			{
				y -= 1;
			}
			break;
		case east:
			if ((x+1) < GRIDMAX_X)
			{
				x += 1;
			}
			break;
		case west:
			if ((x-1) >= 0)
			{
				x -= 1;
			}
			break;
		default:
			break;
	}

	if (ptr_grid->tile[x][y].type == door_closed)
	{
		ptr_grid->tile[x][y].type = door_open;
	}

}

void close(struct Command* ptr_cmd, struct Area* ptr_grid)
{
	int x, y;

	proc_direction(ptr_cmd);

	x = *ptr_cmd->mon->pos.x;
	y = *ptr_cmd->mon->pos.y;

	switch (ptr_cmd->dir)
	{	case north:
			if ((y+1) < GRIDMAX_Y)
			{
				y += 1;
			}
			break;
		case south:
			if ((y-1) >= 0)
			{
				y -= 1;
			}
			break;
		case east:
			if ((x+1) < GRIDMAX_X)
			{
				x += 1;
			}
			break;
		case west:
			if ((x-1) >= 0)
			{
				x -= 1;
			}
			break;
		default:
			break;
	}

	if (ptr_grid->tile[x][y].type == door_open)
	{
		ptr_grid->tile[x][y].type = door_closed;
	}

}

// used to wait ie no cmd key is pressed
void wait_cmd(struct Command* ptr_cmd, struct Area* ptr_grid)
{

	return;
}

// not sure what this was supposed to be for...
enum Direction arrow_keys(char direction)
{
	getch();
	direction = getch();
	
	switch (direction)
	{
		case 'A':
			return north;
		case 'B': 
			return south;
		case 'C':
			return east;
		case 'D':
			return west;
		default:
			return none;
	}

}


