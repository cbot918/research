#include<stdio.h>					// fn: printf
#include<sys/socket.h>		// fn: socket
#include<netinet/in.h>    // socketaddr_in
#include<stdlib.h>				// fn: exit(0)
#include<strings.h>				// fn: bzero
#include<unistd.h>				// fn: close()
#include<netdb.h>
#include<sys/types.h>

#define MAX 80
#define PORT 8888
#define SA struct sockaddr

// (struct sockaddr*)&servaddr

void handleConn( int connfd){	
	
	char buff[MAX];
	int n;
	bzero(buff, MAX);
	

	read(connfd, buff, sizeof(buff));
	printf("client %d: %s", connfd, buff);
	
	write(connfd, buff, sizeof(buff));
		
}

int main(){
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	// create socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1){
		printf("socket creation failed...\n");
		exit(0);
	}
	printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));  // 重置servaddr的內容


	// init socket state
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr)))!=0){
		printf("socket bind failed...\n");
		exit(0);
	}	
	printf("Socket successfully binded..\n");
	
	// listen
	if( listen(sockfd, 5) != 0 ){
		printf("Listen failed...");
		exit(0);
	}
	printf("Server listening..\n");


	// accpet
	len = sizeof(cli);

	while(1){
		connfd = accept(sockfd, (SA*)&cli, &len);
		if (connfd <0){
			continue;
			//printf("server accept failed...\n");
			//exit(0);
		}
		printf("server accept the client...\n");

		handleConn(connfd);	
	
	}

	close(sockfd);
}
