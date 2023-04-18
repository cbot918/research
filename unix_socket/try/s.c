#include<stdio.h>				// printf()
#include<stdlib.h>			// exit()
#include<sys/socket.h>	// socket(), bind(), listen(), accept()
#include<netinet/in.h>	// for sockaddr_in
#include<unistd.h>			// for read() write()
#include<arpa/inet.h>

#define MAX 80
#define PORT 8891
#define BACKLOG 5
#define TEMP 30

int rwOnce(int sockfd){
	char buff[MAX];
	int nbytes;
	
	nbytes = read(sockfd, buff, sizeof(buff));
	if (nbytes < 0){
		printf("socket read failed\n");
		exit(1);
	}
	if (nbytes == 0){
		printf("socket read with EOF\n");
		return -1;
	}
	printf("receive: %s\n", buff);

	return 0;
}


//int sprintf(char *str, const char *format, [arg1, arg2, ... ]);
// int var =100;
// charint_str[20];

// sprintf(int_str, "%d", var);
// printf("Var: %s", int_str);

void yitos(int input, char* buf){
	int res = sprintf(buf, "%d",input);
}

void cli_info(struct sockaddr_in client, char* hook){
	struct sockaddr_in* client_address = (struct sockaddr_in*) &client;
	char* client_ip = inet_ntoa(client_address->sin_addr);
	int client_port = ntohs(client_address->sin_port);
	printf("client: %s:%d\n", client_ip, client_port);

	char temp[TEMP];
	yitos(client_port, temp);
	hook = temp;
	printf("temp:%s\n", temp);
	printf("temp addr: %p\n", temp);
	printf("hook addr: %p\n", hook);

}

int main(){
	// data
	int sockfd, connfd;
	int bind_res, listen_res, accept_res;
	struct sockaddr_in servaddr, client;
	
	// create socket
	// int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen)
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1 ) {
		printf("create socket failed\n");
		return 1;
	}
	printf("sockfd: %d\n", sockfd);
	

	// bind socket     
	// int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen);
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	
	bind_res = bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if( bind_res == -1 ){
		printf("bind socket failed\n");
		return 1;
	}
	printf("bind socket success\n");
	
	// listen socket
	// int listen(int sockfd, int backlog);
	listen_res = listen(sockfd, BACKLOG);
	if( listen_res == -1) {
		printf("listen failed\n");
		return 1;
	}	
	printf("listen on: %d\n", PORT);
	

	// accept    
	// int accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
	int client_len = sizeof(client);
	//while(1){
		connfd  = accept(sockfd, (struct sockaddr*)&client, (socklen_t*)&client_len);
		if (connfd == -1){
			printf("continue\n");
		}
		printf("connection in\n");
		
		char tempp[TEMP];
		cli_info(client, &tempp);
		printf("tempp addr: %p\n",tempp);
		printf("result: %s\n", tempp);

		//////// work code
		// struct sockaddr_in* client_address = (struct sockaddr_in*) &client;
		// char* client_ip = inet_ntoa(client_address->sin_addr);
		// int client_port = ntohs(client_address->sin_port);
		// printf("client: %s:%d\n", client_ip, client_port);

		

		//rwOnce(sockfd);



	// getInfo
	// int getpeername (int socket, struct sockaddr *addr, socklen_t *length-ptr)
	/*
		struct sockaddr_in info;
		socklen_t *ptr;
		int res;
		res = getpeername(sockfd, (struct sockaddr*)&info, ptr);
		if( res == -1){
			printf("getpeername failed\n");
			exit(1);
		}
		printf("get info success\n");
		
*/

	//}



	return 0;
}


/* socket
 * servaddr
 * bzero
 *
 *
 *
 * */

