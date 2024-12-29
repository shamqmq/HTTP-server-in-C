#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>


#define PORT 1445 
#define BUFFS 1024
#define BACKLOG 5

int main(int argc, char *argv[])
{
	// declaring area


	int sock, sock_opt;
	char* nigga = "nigga\nthis is my server\n";
	struct sockaddr_in address = {0};
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	
	socklen_t address_len = sizeof(address);

	struct sockaddr client = {0};
	socklen_t client_len = sizeof(client);
	int opt = 1;
	ssize_t snt;
	// create the socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (0 > sock)
	{
		perror("socket");
		return -1;
	}

	sock_opt = setsockopt(sock , SOL_SOCKET , SO_REUSEADDR , &opt , sizeof(opt));
	if (0 > sock_opt)
	{
		perror("setsockopt");
		return -1;
	}

	// binding
	if (0 > bind(sock, (struct sockaddr *) &address, address_len))
	{
		perror("bind");
		return -1;
	}
	
	//listening
	if (0 > listen(sock, BACKLOG))  //backlog is the nimber of the users that server can listen to in once
	{
		perror("listen");
		return -1;
	}

	//accepting
	int cl = accept(sock, (struct sockaddr *) &client, (socklen_t *) &client_len);
	if (cl < 0)
	{
		perror("accept");
		return -1;
	}
	//client part
	snt = send(cl, nigga, strlen(nigga), 0);
	
	
	//cleaning
	close(cl);
	return 0;
}
