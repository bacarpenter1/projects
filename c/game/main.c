// main file for YET TO BE NAMED GAME

#include <stdio.h>
#include <ncurses.h>
#include "character.h"
#include "cmd.h"
#include "area.h"
#include "screen.h"
#include "ai.h"

int main()
{
	initscr();
	clear();

	// declare player character as type Character
	struct Character* player, * ptr_monster;
	struct Area* grid;
	enum Direction dir;
	struct Command* game_cmd; 
	char turn = 'p';

	player = init_character();
	ptr_monster = init_character();

//	player->target = ptr_monster;

	ptr_monster->sym = 'X';
	ptr_monster->name = "MONSTER";
	ptr_monster->type = monster;

	printw("%c\n", player->sym);

	grid = init_grid(player);
	add_to_grid(ptr_monster, grid);
	game_cmd = init_game_cmd(player);

	
	print_location(player);

	update_grid(grid);
	update_screen(player, grid);
	refresh();
//	while ( (game_cmd->input = get_cmd()) != CMD_QUIT)

//	while ( game_cmd->code != CMD_QUIT )
//	{
	while ( game_cmd->input != 'q')
	{
//	char temp = '0';
//	while ( temp != 'q' )
//	{ 
	
		if (turn == 'p')
		{
			game_cmd->mon = player;
			//game_cmd->input = getch();
			turn = 'm';
		}
		else
		{
			game_cmd->mon = ptr_monster;
			//game_cmd->input =ai_move();
			turn = 'p';
		}

//		proc_direction(game_cmd);

		
	//	game_cmd = get_cmd();
		process_cmd(game_cmd);
		exec_cmd(game_cmd, grid);
/*		
		if (game_cmd->input == '2')
		{
			dir = south;
		}
		else if (game_cmd->input == '8')
		{
			dir = north;
		}
		else if (game_cmd->input == '4')
		{
			dir = west;
		}
		else if (game_cmd->input =='6')
		{
			dir = east;
		}

//		if ( temp == '8' )
//			dir = north;	
*/		
		//move_mon(player, grid, game_cmd->dir);		
		//move_mon(game_cmd);
		//clear();
		
		//print_location(player);		
		update_grid(grid);				
		

		update_screen(player, grid);
		//print_location(ptr_monster);
		//printw("Turn: %c\n",turn);
		//move(GRIDMAX_Y+1 - *player->pos.y, *player->pos.x);

		//NOTE!! refresh() called here only so cursor and ptr_monster can be printed 
		//correctly!  THIS MUST BE FIXED SO THAT update_screen() takes care of it.
		refresh();
	}

	endwin();	

	clean_character(player);
	clean_character(ptr_monster);
	clean_grid(grid);
	clean_game_cmd(game_cmd);

	return 0;
}


