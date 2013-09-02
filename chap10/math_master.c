/*
This is program tests the user’s math skills. 
It asks the user to find the answer to a 
simple multiplication problem and keeps track of 
how many answers he got right.
The program will keep running forever, unless:
1. The user presses Ctrl-C, or
2. The user takes more than five seconds to answer the question.
When the program ends, it displays the final score and set the exit status to 0.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

int score = 0;

void end_game(int sig){
	printf("\nFinal score: %i\n", score);
	exit(0);
}

int catch_signal(int sig, void (*handler)(int)){
	struct sigaction action;
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	return sigaction(sig, &action, NULL);
}

void times_up(int sig){
	puts("\nTIME'S UP!");
	raise(SIGINT);
}

void error(char *msg){
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1);
}

int main(int argc, char const *argv[])
{
	catch_signal(SIGALRM, times_up);
	catch_signal(SIGINT, end_game);
	srandom(time (0));
	while(1){
		//a and b will be randum numbers from 0 to 10
		int a = random() % 11;
		int b = random() % 11;
		char txt[4];
		alarm(5);
		printf("\nWhat is %i times %i\n", a, b);
		fgets(txt, 4, stdin);
		int answer = atoi(txt);
		if(answer == a * b)
			score++;
		else
			printf("\nWrong! Score: %i\n", score);
	}
	return 0;
}