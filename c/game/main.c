// main file for YET TO BE NAMED GAME

#include <stdio.h>
#include <ncurses.h>
#include "character.h"
#include "cmd.h"
#include "area.h"
#include "screen.h"

int main()
{
	initscr();
	clear();

	// declare player character as type Character
	struct Character* player;
	struct Area* grid;
	enum Direction dir;
	struct Game_cmd* game_cmd; 


	player = init_character();
	grid = init_grid();
	game_cmd = init_game_cmd(player);

//	player.name = "Ben";
//	player.pos->x = 0;
//	player.pos->y = 0;
	
//	printw("%s at (%d,%d)\n", player->name, *player->pos.x, *player->pos.y);
	print_location(player);
	print_grid(grid);

	// temp demo of movement
//	for (int i = 0; i < 3;i++)
//	while ( (game_cmd->input = get_cmd()) != CMD_QUIT)

//	while ( game_cmd->cmd != CMD_QUIT )

	while ( game_cmd->input != 'q')
	{
//	char temp = '0';
//	while ( temp != 'q' )
//	{	
//		cbreak();	
//		temp = getch();
		game_cmd->input = getch();
			
	//	game_cmd = get_cmd();
	//	cmd_process(cmd);
		
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
		
		move_mon(player, grid, dir);		
		
		print_location(player);

		print_grid(grid);

		refresh();

		

		update_screen(player, grid);
	}

	endwin();	

	clean_character(player);
	clean_grid(grid);
	clean_game_cmd(game_cmd);

	return 0;
}


