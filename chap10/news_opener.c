/*
This program displays the results from rssgossip.py 
in a web browser. It uses pipe to open the browser
as soon as a story is found by rssgossip.py.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

void error(const char*);
void open_url(const char *);

//exit function to display the cause of failure
void error(const char* msg){
	fprintf(stderr, "%s :%s\n", msg, strerror(errno));
	exit(1);
}
/*
A better way to write this function is to use
calls to exec() and fork() functions
*/
void open_url(const char *url){
	char launch[255];
	sprintf(launch, "cmd /c start %s", url);
	system(launch);
	sprintf(launch, "x-www-browser '%s' &", url);
	system(launch);
	sprintf(launch, "open '%s'", url);
	system(launch);
}

int main(int argc, char const *argv[])
{
	const char *phrase = argv[1];
	const char *vars[] = {"RSS_FEED=http://www.cnn.com/rss/celebs.xml", NULL};
	int fd[2]; //this will store the file discriptors of the pipe
	if(pipe(fd) == -1){
		error("Can't create the pipe");
	}

	pid_t pid = fork();
	if(pid == -1){
		error("Can't fork process");
	}
	if (!pid)
	{
		//this is in the child process
		dup2(fd[1], 1); //set stdout to the write end of the pipe
		close(fd[0]); //close the read end for the child
		if (execle("/usr/bin/python2", "/usr/bin/python2", "./rssgossip.py",
			"-u", phrase, NULL, vars) == -1) //-u tell rssgossip.py to show URLs
		{
			error("Can't run script");
		}
	}
	
	//this is in the parent process
	dup2(fd[0], 0); //redirect stdin to the write end of pipe
	close(fd[1]); //close write end of the pipe
	char line[255];
	while(fgets(line, 255, stdin)){ //same as replace stdin with fd[0]
		/*
		If a line starts with a tab then it's a URL
		*/
		if(line[0] == '\t')
			open_url(line + 1);//goto char after '\t' to access string
	}

	return 0;
}