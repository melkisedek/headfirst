/*
This program demonstrates the use of posix threads
Compile with -lpthread flag to link threads library.
the sleep function is used because the threads run so
fast that without it the function that is called first
would finish before second one has begun. Try removing 
sleep function and run the program several times to see it.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

//display error messages
void error(const char *msg){
	fprintf(stderr, "%s: %s\n", msg, strerror(errno) );
	exit(1);
}
//does_not() and does_too() must have a void* return type
void* does_not(void *a){
	int i = 0;
	for(i = 0; i < 5; i++){
		sleep(1);
		puts("Does not!");
	}
	return NULL;
}

void* does_too(void *a){
	int i = 0;
	for(i = 0; i < 5; i++){
		sleep(1);
		puts("Does too!");
	}
	return NULL;
}

int main(int argc, char const *argv[])
{
	pthread_t t0; //these record all info about the thread
	pthread_t t1;
	//create thread
	if (pthread_create(&t0, NULL, does_not, NULL) == -1) 
		error("Can't create thread t0");
	if(pthread_create(&t1, NULL, does_too, NULL) == -1)
		error("Can't create thread t1");
	
	//void pointer returned by each function will be stored here
	void* result; 
	//waits for a thread to finish
	if(pthread_join(t0, &result) == -1) 
		error("Can't join thread t0");
	if(pthread_join(t1, &result) == -1)
		error("Can't join thread t1");
	return 0;
}