#include<string.h>
#include<stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "struc.h"  
#define SERV_PORT 5000
#define MAXLINE   1024 
#define myip "192.168.1.140"
void tostring(char str[], int num)

{
	int i, rem, len = 0, n;
	n = num;
	while (n != 0)
	{
		len++;
		n /= 10;
	}
	for (i = 0; i < len; i++)
	{
		rem = num % 10;
		num = num / 10;
		str[len - (i + 1)] = rem + '0';
	}
	str[len] = '\0';
}
int main()
{
	int i=0,j=0,sret;
	fd_set readfds;
	struct timeval timeout;
	char str1[15];
	char str[]="192.168.1.";
	int sockfd;
	int n, fd;
	socklen_t len;
	char buf[MAXLINE];
	route r[100];
	struct sockaddr_in servaddr, cliaddr;
	len=sizeof(cliaddr);
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(myip);
	servaddr.sin_port = htons(SERV_PORT);
	bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
	cliaddr.sin_family=AF_INET;
        cliaddr.sin_port=htons(SERV_PORT);
        cliaddr.sin_addr.s_addr=inet_addr("192.168.1.140");
	fcntl (sockfd,F_SETFL,O_NONBLOCK);
	while(i<255)
	{

		tostring(str1,i);
		strcat(str,str1);
		printf("%s\n",str);
		cliaddr.sin_family=AF_INET;
		cliaddr.sin_port=htons(SERV_PORT);
		cliaddr.sin_addr.s_addr=inet_addr(str);
		if(!strcmp(myip,str)==0)
		sendto(sockfd, "hi", strlen("hi"), 0, (struct sockaddr *) & cliaddr, len);
		FD_ZERO(&readfds);	
                FD_SET(sockfd,&readfds);
                timeout.tv_sec=0;
                timeout.tv_usec=5000;
                sret=select(sockfd+1		,&readfds,NULL,NULL,&timeout);
		printf("sret%d\n",sret);
		if(sret==0)
		{
			printf("TIMEOUT\n");
		}
		else
		{
			n=recvfrom(sockfd, buf, MAXLINE, 0, (struct sockaddr *) & cliaddr, &len);
			if(n>0)
			{
				printf("%s\n",buf);
				strcpy(r[j].ip,inet_ntoa(cliaddr.sin_addr));
				printf("%s\n",r[j].ip);
				j++;
			}
			
		}
		strcpy(str,"192.168.1.");
	i++;
	}
	for(int k=0;k<=j;k++)
	{
		printf("ip:%s\n",r[k].ip);
	}

}
