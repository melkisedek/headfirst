/*This program writes timestamped text to a logfile.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*This function returns a string containing the current date*/
char* now(){
	time_t t;
	time (&t);
	return asctime(localtime (&t));
}

int main(){
	char comment[80];
	char cmd[120];
	fgets(comment, 80, stdin);
	sprintf(cmd, "echo '%s %s' >> reports.log", comment, now());
	system(cmd);
	return(EXIT_SUCCESS);
}
