#include <sys/socket.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include "struc.h"  
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#define SERV_PORT 5000
#define MAXLINE   1024 
char *end= "END";

int main(int argc, char **argv)
{
	int sockfd, res, n, fd;
	struct sockaddr_in servaddr, cliaddr;
	int frame_id=0;
	struct timeval timeout;
	char buf[MAXLINE], buf1[MAXLINE];
	fd_set readfds;
	frame frame_recv; 
	frame frame_send;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr =inet_addr("192.168.1.140");
	servaddr.sin_port = htons(SERV_PORT);
	bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	socklen_t len;
	len =sizeof(cliaddr);
	n = recvfrom(sockfd, buf, MAXLINE, 0, (struct sockaddr *) & cliaddr, &len);
	buf[n] = 0;
	printf("client found: [%s]\n", buf);
	sendto(sockfd, "hi", strlen("hi"), 0, (struct sockaddr *) & cliaddr, len);
}
