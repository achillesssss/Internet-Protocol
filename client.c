#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>

void error(const char* msg){
	perror(msg);
	exit(1);
}

// client
// create a socket() 
// connect() socket to server address
// read() and write()
int main(int argc, char* argv[]){
	int sockfd,n, portnum;
	char buffer[256];
	struct sockaddr_in server_addr;
	struct hostent *server;
	if (argc < 3){
		fprintf(stderr, "Error: no port is provided" );
		exit(0);
	}
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0){
		error("can't create socket");
	}
	server = gethostbyname(argv[1]);
	if(server == NULL){
		fprintf(stderr,"ERROR, no such host");
		exit(0);
	}
	portnum = atoi(argv[2]);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portnum);
	bcopy((char *)server->h_addr,(char *) &server_addr.sin_addr.s_addr, server->h_length);
	if(connect(sockfd,(struct sockaddr *) &server_addr,sizeof(server_addr)) < 0)
		error("ERROR: can't connect to server\n");
	printf("Please enter the message: ");
    fgets(buffer,255,stdin);
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    n = read(sockfd,buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
    close(sockfd);
	return 0;
}