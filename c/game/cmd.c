// contains command definitions

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "character.h"
#include "area.h"
#include "cmd.h"

// get the command 
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

#define NUM_CMDS 9
const struct Game_cmd cmd_list[] = 
{
	//cmd_code, dir, Character*, handler_fn
	{ CMD_WAIT, wait_cmd },
	{ CMD_MOVE, move_mon },
	{ CMD_OPEN, open },
	{ CMD_CLOSE, close },
	{ CMD_DOWN, go_down },
	{ CMD_UP, go_up },
	{ CMD_INV, list_inventory },
	{ CMD_GET, get_item },
	{ CMD_DROP, drop_item }

};
//
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
// determine direction from input
enum Direction proc_direction(struct Command* ptr_cmd)
{
	noecho();
	char direction;
	if (ptr_cmd->input > '0' &&  ptr_cmd->input <= '9')
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
//	else if (ptr_cmd->input == 'o' || ptr_cmd->input == 'c')
	else
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
	else if (ptr_cmd->input == '>')
	{
		ptr_cmd->code = CMD_DOWN;
	}
	else if (ptr_cmd->input == '<')
	{
		ptr_cmd->code = CMD_UP;
	}
	else if (ptr_cmd->input == 'i')
	{
		ptr_cmd->code = CMD_INV;
	}
	else if (ptr_cmd->input == 'g')
	{
		ptr_cmd->code = CMD_GET;
	}
	else if (ptr_cmd->input == 'd')
	{
		ptr_cmd->code = CMD_DROP;
	}
	else
	{
		ptr_cmd->code = CMD_WAIT;
	}
}
// execute command
void exec_cmd(struct Command* ptr_cmd, struct Area* ptr_grid)
{
	int x,y;

	for (int i = 0; i < NUM_CMDS /*&& ptr_cmd->code != cmd_list[i].cmd */; i++)
	{	
		// iff game codes match, execute
		if (ptr_cmd->code == cmd_list[i].cmd)
		{
			cmd_list[i].fn(ptr_cmd, ptr_grid);
		
			x = *ptr_cmd->mon->pos.x;
			y = *ptr_cmd->mon->pos.y;
			ptr_grid->tile[x][y].mon = ptr_cmd->mon;

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
	struct Coordinate* temp;

	proc_direction(ptr_cmd);

	int x = *ptr_cmd->mon->pos.x;
	int y = *ptr_cmd->mon->pos.y;

	ptr_grid->tile[x][y].mon = NULL;
// ADDED FOR NEW LOCATION TEST
	temp = new_location(x, y, ptr_cmd->dir);	

	x = *temp->x;
	y = *temp->y;
// END ADDITON
/*	switch (ptr_cmd->dir)
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
		case nwest:
			if ((x - 1) >= 0 && (y+1) < GRIDMAX_Y)
			{
				x -= 1;
				y += 1;
			}
			break;
		default:
			break;
	}
*/
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
		}
	}

	clean_coordinate(temp);
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
	struct Coordinate* temp;

	proc_direction(ptr_cmd);


	x = *ptr_cmd->mon->pos.x;
	y = *ptr_cmd->mon->pos.y;

	temp = new_location(x, y, ptr_cmd->dir);	

	x = *temp->x;
	y = *temp->y;
/*
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
*/
	if (ptr_grid->tile[x][y].type == door_closed)
	{
		ptr_grid->tile[x][y].type = door_open;
	}
	else
	{
		move(0,0);
		printw("Nothing to open!");
		getch();
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
	else
	{
		move(0,0);
		printw("Nothing to close!");
		getch();
	}

}

// used to wait ie no cmd key is pressed
void wait_cmd(struct Command* ptr_cmd, struct Area* ptr_grid)
{

	return;
}

void go_down(struct Command* ptr_cmd, struct Area* ptr_grid)
{

	int x,y;

	x = *ptr_cmd->mon->pos.x;
	y = *ptr_cmd->mon->pos.y;
	
	if (ptr_grid->tile[x][y].type == down_stair)
	{
		gen_level(ptr_grid);
		ptr_grid->tile[x][y].type = up_stair;
	}
	else
	{
		printw("No stair there!");
		getch();
	}
}
	
void go_up(struct Command* ptr_cmd, struct Area* ptr_grid)
{

	int x,y;

	x = *ptr_cmd->mon->pos.x;
	y = *ptr_cmd->mon->pos.y;

	if (ptr_grid->tile[x][y].type == up_stair)
	{
		gen_level(ptr_grid);
		ptr_grid->tile[x][y].type = down_stair;
	}
	else
	{
		printw("No stair there!");
		getch();
	}
}

// lists inventory
void list_inventory(struct Command* ptr_cmd, struct Area* ptr_grid)
{
	WINDOW* win_inventory; 

	win_inventory = newwin(INVENTORY_SIZE+2,INVWIN_XWIDTH+2, INVWIN_YPOS, INVWIN_XPOS-2);


	printw("Inventory:");
	wborder(win_inventory, '|', '|', '-', '-', '+', '+', '+', '+');
	wmove(win_inventory, 1 , 1);

	for (int i = 0; i < INVENTORY_SIZE; i++)
	{
		wmove(win_inventory, i+1, 1);
		wprintw(win_inventory, "%c) %s", 'a'+i, ptr_cmd->mon->inventory[i].name);
	}
	
	//wprintw(win_inventory,"TEST");
	wrefresh(win_inventory);
	move(0,10);
	getch();

	delwin(win_inventory);

	

	
}

// get an item from the floor 
void get_item(struct Command* ptr_cmd, struct Area* ptr_grid)
{
	int x, y, index;

	// get player position	
	x = *ptr_cmd->mon->pos.x;
	y = *ptr_cmd->mon->pos.y;

	index = 0;

	if (ptr_grid->tile[x][y].item != NULL)  
	{
		if (ptr_grid->tile[x][y].item->type != no_item)  
		{	while (ptr_cmd->mon->inventory[index].type != no_item)
			{
				index++;
			}
		
			if (index < INVENTORY_SIZE)
			{
				ptr_cmd->mon->inventory[index] = *ptr_grid->tile[x][y].item;
				free(ptr_grid->tile[x][y].item);
				ptr_grid->tile[x][y].item = NULL;
			}
			else
			{
				printw("Inventory Full");
			}
		}
	}
	else
	{
		printw("Nothing to pick up!");
	}
}
// drop an item on the floor
void drop_item(struct Command* ptr_cmd, struct Area* ptr_grid)
{
	int x, y, index;

	// get player position	
	x = *ptr_cmd->mon->pos.x;
	y = *ptr_cmd->mon->pos.y;

	index = 0;

	printw("Which item? ");
	
	// convert char input to index
	index = getch() - 'a';
	
	if (ptr_grid->tile[x][y].item == NULL)
	{
		ptr_grid->tile[x][y].item = malloc(sizeof(struct Item));
		*ptr_grid->tile[x][y].item = ptr_cmd->mon->inventory[index];

		ptr_cmd->mon->inventory[index].name = " ";
		ptr_cmd->mon->inventory[index].type = no_item;
		ptr_cmd->mon->inventory[index].symbol = ' ';
	}
	else
	{
		printw("There's something there!");
	}
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

struct Coordinate* new_location( int x, int y, enum Direction dir)
{
	struct Coordinate* temp;

	temp = malloc(sizeof(struct Coordinate));

	temp->x = malloc(sizeof(int));
	temp->y = malloc(sizeof(int));

	switch (dir)
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
		case neast:
			if ((x+1) < GRIDMAX_X)
			{
				x += 1;
			}
			
			if ((y+1) < GRIDMAX_Y)
			{
				y += 1;
			}
			break;
		case nwest:
			if ((x-1) >= 0)
			{
				x -= 1;
			}
		
			if ((y+1) < GRIDMAX_Y)
			{
				y += 1;
			}
			break;	
		case swest:
			if ((x-1) >= 0)
			{
				x -= 1;
			}
		
			if ((y-1) >= 0)
			{
				y -= 1;
			}
			break;	
		case seast:
			if ((x+1) < GRIDMAX_X)
			{
				x += 1;
			}
		
			if ((y-1) >= 0)
			{
				y -= 1;
			}
			break;	

		default:
			break;
	}

	*temp->x = x;
	*temp->y = y;

	return temp;
}	
