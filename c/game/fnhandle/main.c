#include <stdio.h>
#include <stdlib.h>

typedef void (*handler_fn)(int n);
void print_crunch(int n);
void print_bang(int n);

struct test
{
	char ID;
	handler_fn fn;
};

const struct test list[] =
{
	{ 'A', print_crunch},
	{ 'B',  print_bang}
};	

int main()
{
/*	struct test test_fn;
	
	test_fn.fn = print_crunch;

	test_fn.fn(5);

	test_fn.fn = print_bang;

	test_fn.fn(5);
*/

	char test = 'A';

	for( int i = 0; i < 2; i++ )
	{
		if ( test == list[i].ID )
		{
			list[i].fn(5);
		}
	}

	return 0;
}

void print_crunch(int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			printf("#");
		}

		printf("\n");
	}
}

void print_bang(int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("!");
	}
	printf("\n");

}
