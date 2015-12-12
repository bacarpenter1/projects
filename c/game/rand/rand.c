#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int random_int()
{
	srand(time(NULL));

	int integer = rand() % 100000;

	return integer;
}

int main()
{
	int integer = 0;

	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", random_int());
	}

	return 0;
}


