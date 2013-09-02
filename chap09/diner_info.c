#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	printf("Dinner: %s\n", argv[1]);
	//getenv() in stdib.h lets you read environment variables
	printf("Juice: %s\n", getenv("JUICE"));
	return 0;
}