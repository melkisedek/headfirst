#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
//uncomment to see output. Don't uncomment everything, this a demo
int main(int argc, char const *argv[])
{
	{
	// char *my_env[] = {"FOOD=coffee", NULL};
	// if(execle("./coffee", "./coffee", "donuts", NULL, my_env) == -1){
	// 	fprintf(stderr,"Can't run process 0: %s\n", strerror(errno));
	// 	//donuts with coffee
	// 	return 1;
	// }
	// char *my_env[] = {"FOOD=donuts", NULL};
	// if(execle("./coffee", "./coffee", "cream", NULL, my_env) == -1){
	// 	fprintf(stderr,"Can't run process 0: %s\n", strerror(errno));
	// 	//cream with donuts
	// 	return 1;
	// }
	// if(execl("./coffee", "coffee", NULL) == -1){
	// 	fprintf(stderr,"Can't run process 0: %s\n", strerror(errno));
	// 	//coffee with coffee
	// 	return 1;
	// }
	char *my_env[] = {"FOOD=donuts", NULL};
	if(execle("./coffee", "coffee", NULL, my_env) == -1){
		fprintf(stderr,"Can't run process 0: %s\n", strerror(errno));
		//coffee with donuts
		return 1;
	}

	fprintf(stderr, "Can't create order: %s\n", strerror(errno) );
	return 1;
	}
	return 0;
}