// demonstrate ptrs with structs

#include <stdio.h>
#include <stdlib.h>

struct pos
{
	int* x,* y;
};

int main()
{
	struct pos* test = malloc(sizeof(struct pos));
	test->x = malloc(sizeof(int));
	test->y = malloc(sizeof(int));

	*(test->x) = 1;

	printf("%d\n", *(test->x));
//*/
//	free(test->x);
//	free(test->y);
	free(test);

	return 0;
}
