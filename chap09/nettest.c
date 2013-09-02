#include <stdio.h>
#include <unistd.h> 
#include <errno.h>//errno variable
#include <string.h> //help display errors with strerror function

int main(int argc, char const *argv[])
{
/*
execl because accepts path of programis known. If execl returned -1 it failed
therefore there statements in braces should be run
*/
	if (execl("/usr/bin/ifconfig","/usr/bin/ifconfig", NULL) == -1)		
	
		//execlp searches on path for program. check -1 in case of failure
		if (execlp("ipconfig", "ipconfig", NULL) == -1){
			fprintf(stderr, "Cannot run ipconfig: %s\n", strerror(errno));
			/*strerror displays error message associated with 
			the errno (error number). Return 1 to show failure
			*/
			return 1;
		}
	return 0;
}
