#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8891
#define HOST "127.0.0.1"

int main(){

	int sockfd ;
	struct sockaddr_in connaddr;
	int connect_res;

	// create socket
	// int socket(int domain, int type, int protocol)
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		printf("create socket failed\n");
		return 1;
	}
	printf("socket created.\n");

	// connect socket   
	// int connect(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen)
	connaddr.sin_family = AF_INET;
	connaddr.sin_addr.s_addr = inet_addr(HOST);
	connaddr.sin_port = htons(PORT);
	
	connect_res = connect(sockfd, (struct sockaddr*)&connaddr, sizeof(connaddr));
	if( connect_res == -1 ){
		printf("connect socket failed\n");
		return 1;
	}
	printf("socket connected.\n");

	char message[] = "hihi\n";
	int nbytes;
	nbytes = write(sockfd, message, sizeof(message));
	if(nbytes < 0){
		printf("socket write failed\n");
		exit(1);
	}
	printf("write success\n");

	return 0;
}
