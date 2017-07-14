#include "header.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{	
	int x,y, i ,j;

	printf("Input x and y\n");
	scanf("%d%d", &x, &y);

	i = addition(x, y);
	j = substraction(x, y);
 
	printf("%d\n", i);
	printf("%d\n", j);
	return 0;
}
