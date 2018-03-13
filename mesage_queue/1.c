#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/msg.h>
#include<sys/types.h>
#include<sys/sem.h>
int main()
{
	int i=5,k,fret;
	struct
	{
		long type;
		int a;
		int b;
		char msgt[20];
	}msg;
	struct
	{
		long type;
		char msgt[20];
	}msgs;
	k=msgget(123,IPC_CREAT|0666);
	if(k<0)
		fprintf(stderr,"message queue is not initialize",k);
	fret=fork();
	if(fret==0)
	{
		printf("Child is start\n");
		strcpy(msg.msgt,"hello nigar");
		msg.a=10;
		msg.b=11;
		msg.type=11;
		msgsnd(k,&msg,30,0);
	}
	else
	{
		k=msgget(123,IPC_CREAT|0666);
		printf("parent is start\n");
		wait();
		msgrcv(k,&msg,30,12,0);
		printf("recieve value:%s \n",msg.msgt);
		printf("msg.a:%d\n",msg.a);
		printf("msg.b:%d\n",msg.b);
	}
}
