#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

#include<arpa/inet.h>


#define MAX 80
#define PORT 8888
#define SA struct sockaddr


void handleConn( int sockfd ){
	
	char hello[7] = "hello\n";
	char buff[MAX];
	bzero(buff, MAX);
	
	write(sockfd, hello, sizeof(hello));

	read(sockfd, buff, sizeof(buff));
	printf("server: %s\n", buff);

}


int main(){
	int sockfd;
	struct sockaddr_in servaddr, cli;

	// create socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1){
		printf("sock create failed \n");
		exit(0);
	}
	printf("sock create success\n");


	// socket connect
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	if( connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0 ){
		printf("socket connect failed..\n");
		exit(0);
	}
	printf("connect to server\n");


	handleConn(sockfd);


	close(sockfd);

}
