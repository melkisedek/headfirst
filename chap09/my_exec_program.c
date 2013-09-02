/*
calls the diner_info program and 
passes it env variables(arguments). Note that the program 
name should be the full to prevent ambiguity and improve 
security. e.g "/home/username/headfirst/diner_info" 
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	/*
	This sets the env variable. Include that to 
	be sure the array terminates always!
	*/
	char *my_env[] = {"JUICE=peach and apple", NULL};

	execle("./diner_info","./diner_info", "4", NULL, my_env);
	/*
	If the execle worked this line of code will never run
	*/
	puts("Dude - the diner_info code must be busted");
	return 0;
}