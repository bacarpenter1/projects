#include <stdio.h>
#include <stdlib.h>

int main()
{
	char* string = malloc(sizeof(char));
	
	*(string) ='!';
/*
	string = realloc( string, sizeof(char)*2);

	*(string+1) = '#';
*/

/*	char* temp = malloc(sizeof(char));

	temp = string;

	string = malloc(sizeof(char)*2);

	*(string) = *temp;

	*(string+1) = '#';
	
	free(temp);
*/
	printf("%c\n", *string);

	free(string);

	return 0;
}
