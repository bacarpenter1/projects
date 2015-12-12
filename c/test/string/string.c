// take input of a single string using pointers

#include <stdio.h>
#include <stdlib.h>

#define BUFFSIZE 100

// getst gets the string, printstr prints it
char* getstr( char* input );
void printstr( char* input );

int main()
{
	char* string;

//	string  = malloc(sizeof(char));

	string = getstr( string );

	printf("------------\n");

	printstr( string );	

	free( string );

//	printf("%s\n", string);

	return 0;
}

char* getstr( char* input )
{

	int n = 0;	
	char scanned = 'Q';
	char* ptrTemp;
	char* ptrDel;
	
	ptrTemp = input = &scanned;
	
	printf("Enter String\n");
	

	// allocate a new memory location for each char while the string is valid
	
	while ( scanned != '\n' )
	{
		scanned = getchar();
		ptrTemp = malloc(sizeof(char)*(n+2));
		*(ptrTemp+n) = scanned;
	
		//DEBUG
		printf("#%d\n", n);
		printf("%c\n", scanned);
		printf("%c\n", *(ptrTemp+n));
		
		printf("BREAK");

	

		printf("_BREAK_");
		
		if ( n < 1 )
		{
			input = ptrTemp;
		}
		else
		{
			for ( int k = 0; k < n; k++ )
			{
				*(ptrTemp+k) = *(input+k);
			
			}
		}

		*(ptrTemp+1+n) = '\0';

		for ( int k = 0; *(input+k) != '\0' ; k++ )
		{
			printf("%c", *(input+k));
		}
		n++;		
		printf("\n\n%s\n", input);
		ptrDel = input;
		input = ptrTemp;
	}

//	ptrDel = input;
//	input = ptrTemp;

	free(ptrDel);
	
	return input;
}

void printstr( char* input )
{
	for( int n = 0; *(input+n) != '\0'; n++ )
	{
		printf("%c", *(input+n));
	}

	printf("\n");
}
