/*
 * =====================================================================================
 *
 *       Filename:  client.c
 *        Version:  1.0
 *        Created:  2014年06月05日 19时02分44秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/sendfile.h>

#define PORT 9527
#define BUF 2048
#define BACKLOG 10
#define size 100
#define TRUE 1
#define FALSE 0

int setnonblocking(int sockfd){
    if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK) == -1) {
        return -1;
    }
    return 0;
}


int main(int argc, char *argv[]){
	int listenfd,connfd,n;
	int epoll_fd,cur_fd,newfd,number,stop;
	struct epoll_event ev;
	struct epoll_event events[size];
	struct sockaddr_in server_address,client_address;
	struct stat stat_buf;
	const char* file_name=argv[1];
	char buffer[BUF];

	int file_ptr=open(file_name,O_RDONLY);
	fstat(file_ptr,&stat_buf);
	close(file_ptr);
	bzero(&server_address,sizeof(server_address));
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=htonl(INADDR_ANY);
	server_address.sin_port=htons(PORT);

	if((listenfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		exit(0);
	}
	setnonblocking(listenfd);
	int opt=1;
	setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
	if(bind(listenfd,(struct sockaddr*)&server_address,sizeof(server_address))==-1){
		exit(0);
	}
	if(listen(listenfd,BACKLOG)==-1){
		exit(0);
	}

	epoll_fd=epoll_create(10);
	ev.data.fd=listenfd;
	ev.events=EPOLLIN | EPOLLET;
	epoll_ctl(epoll_fd,EPOLL_CTL_ADD,listenfd,&ev);
	cur_fd=1;stop=FALSE;
	socklen_t len=sizeof(struct sockaddr_in);
	while(!stop){
		number=epoll_wait(epoll_fd,events,cur_fd,-1);
		assert(number!=-1);
		for(n=0;n<number;n++){
			connfd=events[n].data.fd;
			if(connfd==listenfd){
				while((newfd=accept(listenfd,(struct sockaddr*)&client_address,&len))>0){
					printf("connect with %s ,socket index %d\n",\
								inet_ntoa(client_address.sin_addr),newfd);
					setnonblocking(newfd);
					ev.data.fd=newfd;
					ev.events=EPOLLIN|EPOLLET|EPOLLHUP;
					if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,newfd,&ev)==-1){
						perror("epoll_ctl:add");
						exit(0);
					}
					cur_fd++;
				}
				if(newfd==-1){
					if(errno!=EAGAIN&&errno!=ECONNABORTED\
								&&errno!=EPROTO&&errno!=EINTR){
						perror("accept");
					}
				}
				continue;
			}else if(events[n].events & EPOLLOUT){
				printf("start to sendfile !\n");
				int ret=0,left=stat_buf.st_size;
				file_ptr=open(file_name,O_RDONLY);
				while(left>0){
					ret=sendfile(connfd,file_ptr,NULL,BUF);
					if(ret<0||errno==EAGAIN){
						continue;
					}else if(ret==0){
						break;
					}else{
						left-=ret;
					}
				}
				printf("sendfile over !\n");
				close(file_ptr);
				ev.data.fd=connfd;
				epoll_ctl(epoll_fd,EPOLL_CTL_DEL,connfd,&ev);
				cur_fd--;
				close(connfd);
			}else if(events[n].events & EPOLLIN){
				char msg[100];
				memset(msg,'\0',100);
				int ret=recv(connfd,msg,100,0);
				if(ret<=0){
					close(connfd);
				}
				printf("recv from client : %s\n",msg);
				ev.data.fd=connfd;
				ev.events=EPOLLOUT|EPOLLET|EPOLLHUP;
				epoll_ctl(epoll_fd,EPOLL_CTL_MOD,connfd,&ev);
			}
		}

	}
	close(listenfd);
	return 0;
}

