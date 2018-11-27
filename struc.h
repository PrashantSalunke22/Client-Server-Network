#include<stdio.h>
#include<stdlib.h>
typedef struct packet
{
	char data[1024];
}packet;
typedef struct frame
{
	int frame_kind;
	int sq_no;
	int ack;
	packet packet;
}frame;
typedef struct route
{
	char ip[16];
}route;
