/*
 * =====================================================================================
 *
 *       Filename:  splice-client.c
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
#include <assert.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define PORT 9527
#define BUF 2048

int main( int argc, char *argv[] ){

	int sockfd,ret;
	int pipefd[2];
	char SEND_BUF[100]={"hello server , I'm login in !"};
	char RECV_BUF[BUF];
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

	ret=send(sockfd,SEND_BUF,100,0);

	while(1){

		ret=pipe(pipefd);
		ret=splice(sockfd,NULL,pipefd[1],NULL,BUF,\
					SPLICE_F_MORE|SPLICE_F_NONBLOCK);
		assert(ret!=-1);
		ret=splice(pipefd[0],NULL,file_ptr,NULL,BUF,\
					SPLICE_F_MORE|SPLICE_F_NONBLOCK);
		if(ret==-1){
		      break;
		}

	}

	close(file_ptr);
	close(sockfd);

	return 0;
}
