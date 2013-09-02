/*
this is the coffee program usedby the test_coffee program.
it is called by an exec function.
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	char *w = (char*)getenv("EXTRA");
	if (!w)
		w = (char*)getenv("FOOD");
	if(!w)
		w =(char*) argv[argc -1];
	char *c = (char*)getenv("EXTRA");
	if(!c)
		c = (char*)argv[argc - 1];
	printf("%s with %s\n", c, w);
	return 0;
}