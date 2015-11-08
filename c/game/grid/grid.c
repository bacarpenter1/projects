//generate a game grid, (x,y) and implement character movement

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define GRIDMAX 10

char get_movement();
char movement( int* x , int* y );
void print_grid( int* x, int* y );

int main()
{
	initscr();
	noecho();	

	// position 
	int* ptr_x;
	int* ptr_y;
	ptr_x = malloc(sizeof(int));
	ptr_y = malloc(sizeof(int));

	*ptr_x = *ptr_y = 0;

	int  moved = 1;


///	for (int i = 0; i < 10; i++ )
	while(moved != 'q')
	{
		//moved = movement(ptr_x, ptr_y);
		
		clear();
	//	printf("\e[2J\e[1;1H");
		printw("Location is: (%d,%d)\n", *ptr_x, *ptr_y);

		print_grid(ptr_x, ptr_y);

		refresh();
		moved = movement(ptr_x,ptr_y);
		
	}

	// grid array
	//int grid[GRIDMAX][GRIDMAX];

	free(ptr_x);
	free(ptr_y);

	endwin();

	return 0;
}

char get_movement()
{	
	printw("Enter movement: ");

	return getch();
}


char movement( int* x, int* y )
{
	char direction = get_movement();

	if (direction == '6')
	{
		*x = *x+1;
	}
	else if (direction == '4')
	{
		*x = *x-1;
	}
	else if (direction == '2')
	{
		*y = *y+1;
	}
	else if (direction == '8')
	{
		*y = *y-1;
	}

	return direction;	
}

void print_grid( int* x, int* y )
{
	for (int j = 0; j < GRIDMAX; j++)
	{
		for (int i = 0; i < GRIDMAX; i++)
		{
			if (*x == i && *y == j)
			{
				printw("@");
			} 
			else
			{
				printw(".");
			}
		}
		
		printw("\n");
	}

	refresh();
}
				
