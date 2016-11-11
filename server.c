#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>



void error(const char* msg){
	perror(msg);
	exit(1);
}

//server: create socket, bind, listen, accept -> read & write

int main(int argc, char* argv[]){
	int sockfd,newsockfd,n, portnum;
	socklen_t client_len;
	struct sockaddr_in server_addr, client_addr;
	char buffer[256];
	if(argc < 2){
		fprintf(stderr, "Error, no port provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	if(sockfd < 0){
		error("Error: no socket is created");
	}
	portnum = atoi(argv[1]);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portnum);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sockfd, (struct sockaddr *)&server_addr,sizeof(server_addr)) < 0)
		error("Error: can't bind ");
	listen(sockfd,10);
	client_len = sizeof(client_addr);
	newsockfd = accept(sockfd,(struct sockaddr *) &client_addr, &client_len);
	if (newsockfd < 0)
		error("Error: can't accept");
	//Read and write data 
	n =  read(newsockfd,buffer,256);
	if (n > 0)
		printf("Mess from client: %s\n",buffer);
	else error("Error reading from client");
	n = write(newsockfd,"server got it",13);
	if (n < 0)
		error("Error: writing to client");
	close(newsockfd);
	close(sockfd);
	return 0;
}