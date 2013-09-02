/*
This program demostrates the hanlding of signal in c.
Do not use stdio in advanced programs, at times it
may not be available. 
*/

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

//this is the signal handler function
void handle_interrupt(int sig){
	puts("Goodbye cruel world....\n");
	exit(1);
}

//this is the function to register a handler
int catch_signal(int sig, void (*handler)(int)){
	struct sigaction action;	  //create an action
	action.sa_handler = handler;  //set handler as passed in function
	sigemptyset(&action.sa_mask); //use empty mask
	action.sa_flags = 0;
	return sigaction (sig, &action, NULL);
}

int main(int argc, char const *argv[])
{
	if (catch_signal(SIGINT, handle_interrupt) == -1)
	{
		fprintf(stderr, "Can't map the handler");
		exit(2);
	}
	char name[30];
	printf("Enter your name: ");
	fgets(name, 30, stdin);
	printf("Hello %s\n", name);
	return 0;
}