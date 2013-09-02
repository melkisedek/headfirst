#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

void error(const char*); //exit function on failure

void error(const char* msg){
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1);
}

int main(int argc, char *argv[])
{
	char *phrase = argv[1];
	const char *vars[] = {"RSS_FEED=http://www.cnn.com/rss/celebs.xml", NULL};
	FILE *f = fopen("stories.txt", "w");
	if (!f) //if f was 0 we couldn't open the file
	{	
		error("Can't open stories.txt");
	}

	pid_t pid = fork();
	if (pid == -1)
	{
		error("Can't fork process");
	}

	if (!pid)
	{
		if (dup2(fileno(f), 1) == -1)
		{
			error("Can't redirect Standard Output");
		}
		if (execle("/usr/bin/python2", "/usr/bin/python2", "./rssgossip.py",
			phrase, NULL, vars) == -1)
		{
			error("Can't run script");
		}
	}

	//variable to store about the process
	int pid_status; 
	
	if (waitpid(pid, &pid_status, 0) == -1)
	{	
		error("Error waiting for child process");
	}
	return 0;
}