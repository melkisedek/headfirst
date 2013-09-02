#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

//display error
void error(const char* msg){
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(1);
}

//create internet streaming socket
int open_listener_socket(){
	int s = socket(PF_INET, SOCK_STREAM, 0);
	if (s == -1)
		error("Can't open socket");
	
	return s;
}

/*
make the socket reusable so that you can 
restart the server without problems
*/
void bind_to_port(int socket, int port){
	struct sockaddr_in name;
	name.sin_family = PF_INET;
	name.sin_port = (in_port_t)htons(30000);
	name.sin_addr.s_addr = htonl(INADDR_ANY);
	int reuse = 1;
	if(setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1)
		error("Can't set the reuse option on the socket");
	int c = bind(socket, (struct sockaddr *)&name, sizeof(name)); //grab port 30000
	if(c == -1)
		error("Can't bind to socket");
}

//sent a string to the client
//And don't terminate server on error
int say(int socket, const char *s){
	int result = send(socket, s, strlen(s), 0);
	if(result == -1)
		fprintf(stderr, "%s: %s\n", "Error talking to the client", strerror(errno));
	return result;
}

int listener_d; //main listener socket for server

/*This function runs when someone presses CRL-C
It will close the socket before terminating
*/
void handle_shutdown(int sig){
	if (listener_d)
		close(listener_d);

	fprintf(stderr, "Bye!\n");
	exit(0);
}

// this allows us to create custom handler functions for signals
int catch_signal(int sig, void (*handler)(int)){
	struct sigaction action;
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	return sigaction(sig, &action, NULL);
}

//simplify the recv function to read data from client
int read_in(int socket, char *buf, int len){ //read all characters until '\n'
	char *s = buf;
	int slen = len;
	int c = recv(socket, s, slen, 0);
	//keep reading until there are no more characters or '\n' is reached
	while((c > 0) && (s[c-1]) != '\n'){ 
		s += c; slen -= c;
		c = recv(socket, s, slen, 0);
	}
	if(c > 0)
		return c; //in case there is an error
	else if (c == 0)
		buf[0] = '\0'; //nothing read, sent back empty string
}

int main(int argc, char const *argv[])
{
	if(catch_signal(SIGINT, handle_shutdown) == -1) //call handle_handle shutdown if CTRL-C pressed
		error("Can't set the interrupt haandler");
	listener_d = open_listener_socket();
	bind_to_port(listener_d, 30000); //create socket on port 30000
	if(listen(listener_d, 10) == -1) //set listen-queue length to 10
		error("Can't isten");
	struct sockaddr_storage client_addr;
	unsigned int address_size = sizeof(client_addr);
	puts("Waiting for Connection");
	char buf[255];
	while(1){
		//listen for a connection
		int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
		if(connect_d == -1)
			error("Can't open secondary socket");
		
		//this creates the child process, if fork returns 0 then you are in the child
		if(!fork()){
			close(listener_d);

			//sent data to the client
			if(say(connect_d, 
					"Internet Knock Knock Protocol Server\r\nVersion 1.0\r\nKnock! Knock!\r\n") != -1){
				read_in(connect_d, buf, sizeof(buf)); //read data from the client
			if(strncasecmp("Who's there?", buf, 12))
				say(connect_d, "You should say 'Who's there?'!");
			else{
				if(say(connect_d, "Oscar\r\n>") != -1){
					read_in(connect_d, buf, sizeof(buf));
					if(strncasecmp("Oscar who?", buf, 10))
						say(connect_d, "You should say 'Oscar who?'\r\n");
					else
						say(connect_d, "Oscar silly question, you get a silly answer\r\n");
					}
				}
			}
			close(connect_d); //close socket to client from child
			exit(0); //let child exit, prevent it from entering main serverloop
		}
		close(connect_d);
	}
	return 0;
}