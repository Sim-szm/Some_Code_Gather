/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *        Version:  1.0
 *        Created:  2014年06月07日 16时31分14秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#define PORT 9527
int main( int argc, char *argv[] ){

	int sockfd;
	char SEND_BUF[100]={"hello server , I'm login in !"};
	char RECV_BUF[2048];
	struct sockaddr_in server;
	const char* file_name=argv[1];

	int file_ptr=open(file_name,O_RDWR|O_CREAT,0666);
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	server.sin_port=htons(PORT);

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(connect(sockfd,(struct sockaddr *)&server,sizeof(server))==-1){
		perror("connect error");
		exit(1);
	}

	int ret=send(sockfd,SEND_BUF,100,0);

	while(1){
		ret=recv(sockfd,RECV_BUF,2048,0);
		if(ret<0){
			break;
		}else if(ret==0){
			break;
		}else{
			write(file_ptr,RECV_BUF,ret);
			bzero(RECV_BUF,sizeof(RECV_BUF));
		}
	}
	close(file_ptr);
	close(sockfd);
	return 0;
}
