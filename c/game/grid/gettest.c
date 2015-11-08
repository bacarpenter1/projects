#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

char getin();

int main()
{
	initscr();
	noecho();
//	fflush(stdout);

	char test = '1';

	printw("Enter Character: ");

	while( 1 )
	{
		test  = getch();

		printw("-%c-\n",test);
		refresh();

		if (test == 'q')
			return 0;
	}

	
	endwin();

	return 0;
}

