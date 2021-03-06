/*
ere is the code for a web client that will
download the contents of a page from Wikipedia and 
display it on the screen. The web page will be passed as 
an argument to the program.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

void error(const char *msg){
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1);
}

int open_socket(char *host, char *port){
	struct addrinfo *res;
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	if(getaddrinfo(host, port, &hints, &res) == -1)
		error("Can't resolve the address");
	int d_sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	if(d_sock == -1)
		error("Can't open socket");
	int c = connect(d_sock, res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);
	if(c == -1)
		error("Can't connect to socket");
	return d_sock;
}

int say(int socket, const char * s){
	int result = send(socket, s, strlen(s), 0);
	if(result == -1)
		fprintf(stderr, "%s: %s\n", "Error talking to the server", strerror(errno));
	return result;
}

int main(int argc, char const *argv[])
{
	int d_sock;
	d_sock = open_socket("en.wikipedia.org", "80");
	char buf[255];
//create a string of the path to the page that you want
	sprintf(buf, "GET /wiki/%s http/1.1\r\n", argv[1]);
	say(d_sock, buf);
//sent a host adddress as well as a blank line
	say(d_sock, "Host: en.wikipedia.org\r\n\r\n");
	char rec[256];
	int bytesRcvd = recv(d_sock, rec, 255, 0);
	while(bytesRcvd){
		if(bytesRcvd == -1)
			error("Can't read from server");
		//add a '\0' to the end to make it a proper c string
		rec[bytesRcvd] = '\0';
		printf("%s\n", rec);
		bytesRcvd = recv(d_sock, rec, 255, 0);
	}

	close(d_sock);
	return 0;
}