#include <stdio.h>

int main()
{
	char array[4],  temp = '0'; 
	int n = 0;

	printf("\n------\n");

	while ( temp != '\n' && n < 4)
	{
		temp = getchar();
		array[n] = temp;
		n++;
		printf("#%d %c\n", n, temp);
	}	


	for ( n = 0; n < 4; n++ )
	{
		printf("%c", array[n]);
	}

	printf("\n");

	return 0;
}
