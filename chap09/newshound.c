/*
This program uses the rssgossip.py script to search rss feeds 
with the phrase passed as an argument.
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	char *feeds[] = {
		"http://www.cnn.com/rss/celebs.xml",
		"http://www.rollingstone.com/rock.xml",
		"http://eonline.com/gossip.xml"
	};
	int times = 3;
	//search terms passed as an argument
	char *phrase = argv[1];
	int i;
	for (i = 0; i < times; i++)
	{
		char var[255];
		sprintf(var, "RSS_FEED=%s", feeds[i]);
		char *vars[] = {var, NULL}; //this is an environment array
		pid_t pid = fork();
		if (pid == -1)
		{
			fprintf(stderr, "Can't fork process: %s\n", strerror(errno));
			return 1;
		}
		if (!pid)
		{
			if (execle("/usr/bin/python2", "/usr/bin/python2",
			"./rssgossip.py",phrase, NULL, vars) == -1)
			{
			fprintf(stderr, "Can't run script: %s\n", strerror(errno));
			return 1;
			}
		}		
	}
	return 0;
}