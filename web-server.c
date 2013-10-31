#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define	FILE_MAX_SIZE	100000	
#define back_log	10	
#define PORT	8080	
#define RECV_SIZE	1024		
#define	SEND_SIZE	100000	
#define	URI_SIZE	128
char *get_uri(char *req_header, char *uri_buf){
	int index = 0;
	while( (req_header[index] != '/') && (req_header[index] != '\0') ){
		index++;
	}
	int base = index;
	while( ((index - base) < URI_SIZE) &&(req_header[index]!=' ') && (req_header[index] != '\0') ){
		index++;
	}
	if((req_header[index - 1] == '/') && (req_header[index] == ' ')){
		strcpy(uri_buf, "index.html");
		return uri_buf;
	}
	strncpy(uri_buf, req_header + base + 1, index - base - 1);
	return uri_buf;

}
int http_session(int *connect_fd, struct sockaddr_in *client_addr){
	char recv_buf[RECV_SIZE + 1];			/* server socket receive buffer */
	unsigned char send_buf[SEND_SIZE + 1];	/* server socket send buffer */
	unsigned char file_buf[FILE_MAX_SIZE + 1];
	memset(recv_buf, '\0', sizeof(recv_buf));
	memset(send_buf, '\0', sizeof(send_buf));
	memset(file_buf, '\0', sizeof(file_buf));
	char uri_buf[URI_SIZE + 1];	/* store the the uri request from client */
	memset(uri_buf, '\0', sizeof(uri_buf));
	int res = 0;
	int read_bytes = 0;
	int send_bytes = 0;
	int file_size = 0;
        char msg_road[URI_SIZE+1]="/var/www/html/";//change the visit direction
	      memset(recv_buf, '\0', sizeof(recv_buf));
              if( (read_bytes = recv(*connect_fd, recv_buf, RECV_SIZE, 0) ) > 0) {
                      memset(uri_buf, '\0', sizeof(uri_buf));

                       if(get_uri(recv_buf, uri_buf) == NULL){}
		              printf("URI:%s\n", uri_buf);
                           strcat(msg_road,uri_buf);
                           strcpy(uri_buf,msg_road);
                      if(access(uri_buf, F_OK)==0&&access(uri_buf, R_OK)==0){  //#define R_OK 4 F_OK 0 .check file 
			          printf("file ok\n");
                     }
                       printf("\n******************************************\n");
		         file_size =  get_file(uri_buf, file_buf);
                       send_bytes=sizeof(send_buf);
                    memcpy(send_buf,file_buf,file_size);
                  
		  send(*connect_fd, send_buf, send_bytes, 0);
              		
	    }
	return 0;
}
int get_file(char *uri_buf, char *file_buf){
	int read_count = 0;
	int fd ;
	if((fd =open(uri_buf, O_RDONLY))==-1)
	{
		perror("open error in get_file");
		return -1;
	}
	if((read_count = read(fd, file_buf, FILE_MAX_SIZE)) == -1)
	{
		perror("read error in get_file ");
		return -1;
	}
	return read_count;
}
int socket_init(int *listen_fd, struct sockaddr_in *server_addr){
	if((*listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket() error");
		return -1;
	}
    int opt=1;
	if(setsockopt(*listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1){
		perror("setsockopt() error");
		return -1;
	}  
	server_addr->sin_family = AF_INET; 
	server_addr->sin_port = htons(PORT); 
	server_addr->sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(*listen_fd, (struct sockaddr *)server_addr, sizeof(struct sockaddr_in)) == -1){
		perror("bind() error.");
		return -1;
	}
	if(listen(*listen_fd, back_log) == -1){
		perror("listen() error.");
		return -1;
	}
	return 0;
}
int main(int argc, char *argv[]){
	int listen_fd;
	int connect_fd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
        memset(&server_addr, 0,sizeof(struct sockaddr_in));
        memset(&server_addr,0, sizeof(struct sockaddr_in));
	if(socket_init(&listen_fd, &server_addr) == -1){
		perror("socket_init() error.");
		exit(1);
	}
	socklen_t addrlen = sizeof(struct sockaddr_in);
	pid_t pid;
	while(1){
		if((connect_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &addrlen)) < 0){
			perror("accept() error");
			continue;
		}
        pid=fork();
		if( pid > 0){

			close(connect_fd);
			continue;
		}
		else if(pid == 0){
			close(listen_fd);
			if(http_session(&connect_fd, &client_addr) == -1){
				perror("http_session() error.");
				shutdown(connect_fd, SHUT_RDWR); //stop the send and recv in this socket
				exit(1);		/* exit from child process, stop this http session  */
			}
                     shutdown(connect_fd,SHUT_RDWR);
                     printf("\nclose connection successfully !\n");
			exit(0);
		}else{
	        	exit(1);
		}
	}
	shutdown(listen_fd, SHUT_RDWR);
	return 0;
}
