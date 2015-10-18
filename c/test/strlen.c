// strlen.c calculates the length of a string

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char* string = malloc(sizeof(char));
	char in;

	printf("Enter String\n");

//	scanf("%c", &in);

//	string = &in;

	scanf(" %c", *&string);

	printf("%c\n", *string);

	return 0;
}
