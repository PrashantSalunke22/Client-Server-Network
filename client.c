#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define BUFFERT 256
int create_client_socket (int port, char* ipaddr);
struct sockaddr_in sock_serv;
int main (int argc, char**argv)
{
	int sfd,fd;
	char buf[BUFFERT];
	off_t  m,sz;
	int count=0;
	long int n;
	int l=sizeof(struct sockaddr_in);
	struct stat buffer;
	if (argc != 4)
	{
		fprintf(stdout,"#####Error: %s <ip_serv> <port_serv> <filename> ####\n",argv[0]);
		return EXIT_FAILURE;
	}
	sfd=create_client_socket(atoi(argv[2]), argv[1]);
	if ((fd = open(argv[3],O_RDONLY))==-1)
	{
		fprintf(stdout,"open fail");
		return EXIT_FAILURE;
	}
	if (stat(argv[3],&buffer)==-1)
	{
		fprintf(stdout,"stat fail");
		return EXIT_FAILURE;
	}
	else
		sz=buffer.st_size;
	bzero(&buf,BUFFERT);
	n=read(fd,buf,BUFFERT);
	while(n)
	{
		if(n==-1)
		{
			fprintf(stdout,"read fails");
			return EXIT_FAILURE;
		}
		m=sendto(sfd,buf,n,0,(struct sockaddr*)&sock_serv,l);
		if(m==-1)
		{
			fprintf(stdout,"send error");
			return EXIT_FAILURE;
		}
		count+=m;
		fprintf(stdout,"data trasferring\t%d\n",count);
		bzero(buf,BUFFERT);
		n=read(fd,buf,BUFFERT);
	}
	m=sendto(sfd,buf,0,0,(struct sockaddr*)&sock_serv,l);
	close(sfd);
	close(fd);
	return EXIT_SUCCESS;
}
int create_client_socket (int port, char* ipaddr)
{
	int l,sfd;
	sfd = socket(AF_INET,SOCK_DGRAM,0);
	if (sfd == -1)
	{
		fprintf(stdout,"socket fail");
		return EXIT_FAILURE;
	}
	l=sizeof(struct sockaddr_in);
	bzero(&sock_serv,l);
	sock_serv.sin_family=AF_INET;
	sock_serv.sin_port=htons(port);
	if (inet_pton(AF_INET,ipaddr,&sock_serv.sin_addr)==0)
	{
		fprintf(stdout,"Invalid IP adress\n");
		return EXIT_FAILURE;
	}
	return sfd;
}
