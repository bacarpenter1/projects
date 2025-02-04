// main file for YET TO BE NAMED GAME

#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include "character.h"
#include "cmd.h"
#include "area.h"
#include "screen.h"
#include "ai.h"

int main()
{
	srand(time(NULL));

	initscr();
	clear();

	noecho();

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

	grid = init_grid(player);
	gen_level(grid);
	add_to_grid(player, grid);
	add_to_grid(ptr_monster, grid);

	//gen_level(grid);

//	print_location(player);

	printw(" Turn: %c\n", turn);
	update_grid(grid);
	update_screen(player, grid);
	refresh();
	
	game_cmd = init_game_cmd(player);
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
//			turn = 'm';
		}
		else
		{
			game_cmd->mon = ptr_monster;
			//game_cmd->input =ai_move();
			turn = 'p';
		}

		process_cmd(game_cmd);
		exec_cmd(game_cmd, grid);
		
		update_grid(grid);				
		clear();

		printw(" Turn: %c\n",turn);
		update_screen(player, grid);

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


