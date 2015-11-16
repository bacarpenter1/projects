#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>

char ai_move()
{
	int dir = 0;

	srand(time(NULL));

	while ((dir < 2) || (dir%2 != 0))
	{
		dir = rand() % 8 + 1;
	}

	dir += 48;

	clear();
	printw("%c\n\n", dir);
	refresh();

	return dir;
}

