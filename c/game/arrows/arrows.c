#include <stdio.h>
#include <ncurses.h>

int main()
{
	WINDOW* testwin;
	keypad(stdscr, TRUE);

	int startx, starty, width, height;
	wchar_t input;

	height = 3;
	width = 10;
	starty = 0;
	startx = 20;


	initscr();
	clear();

	noecho();

	printw("****************************************************************\n");	

	refresh();

	testwin = newwin(height, width, starty, startx);

	wborder(testwin, '|','|','-','-','-','-','-','-');
	wmove(testwin, 1,1);
	wprintw(testwin,"Window");

	wrefresh(testwin);
/*
	input = wgetch(testwin);

	if (input == KEY_F(1))
	{
		wclear(testwin);
		wmove(testwin, 1, 1);
		wprintw(testwin, "F1");
		wrefresh(testwin);
	}

	getch();

*/
	delwin(testwin);

	refresh();

	input = getch();

	printw("%d\n", input);

	if (input == KEY_F(1))
	{
		printw("HELLO!\n");
	}

	refresh();



	return 0;
}	
