// test pointer arith

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n = 0;

	printf("enter size of array: ");
	scanf(" %d", &n);
	//printf("%d\n", n);
	
	char* test = malloc(sizeof(char)*n);
	char temp = 't';

	printf("Enter chars\n");
	scanf(" %c", &temp);

	*(test) = temp;
	*(test+1) = 'r';
/*
	for( int k = 0; k != n; k++
	{
		scanf(
*/
	printf("OUTPUT\n------\n");
	for( int k = 0 ; k < n; k++ )
	{
		printf("%c\n", *(test+k));
	}

	free(test);
	return 0;
}
