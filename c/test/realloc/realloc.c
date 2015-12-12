#include <stdio.h>
#include <stdlib.h>

int main()
{

	char* string = malloc(sizeof(char));
	char scan;// = '\0';
 	int n = 0;

	//scan = getchar();

	for ( n = 0; (scan = getchar()) != '\n'; n++ )
	{
		//scan = getchar();
		
		realloc(string, sizeof(char)*(n+2));
		*(string+n) = scan;

		printf("\n%d_%c\n", n,*(string+n));

		//scan = getchar();	
	}
	
	*(string+n) = '\0';

	printf("\n%d_%s\n", n, string);

	free(string);

	return 0;
}	

