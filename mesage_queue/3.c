#include<stdio.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<sys/sem.h>
#include<sys/types.h>
#include<string.h>
int main()
{
	int i,j=1,k,n,m;
	struct
	{
		long type;
		char sen[200];
	}msg;
	k=msgget(234,IPC_CREAT|0666);
	if(k<0)
		fprintf(stderr,"message queue is not start properly\n",k);
	while(j)
	{
		n=msgrcv(k,&msg,512,12,0);
		if(n<0)
			fprintf(stderr,"message is not receive properly\n",n);
		printf("receive  data is-->%s\n",msg.sen);
		m=strncmp(msg.sen,"end",3);
		if(m ==0)
		{
			j=0;
		}
		fflush(stdout);
	}
	msgctl(k,IPC_RMID,0);
	exit(EXIT_FAILURE);
}
