#include"header.h"
#include"ds.h"
#include"decleration.h"
int main()
{
	int a,rfd,b,wfd,count,l,k;
	Request r,c;
	printf("%d: is pc3 begin\n",getpid());
	k=msgget(12,0666|IPC_CREAT);
	count=msgrcv(k,&r,sizeof(Request),0,0);	
	a=r.oper1;
	b=r.oper2;
	c.pid=r.pid;
	c.result=a*b;
	printf("aa--->%d\n",a);
	printf("bb--->%d\n",b);
	printf("result of pc3-->%d\n",c.result);
	l=msgget(13,0666|IPC_CREAT);
	count=msgsnd(l,&c,sizeof(Request),0);	
	close(wfd);
	printf("%d: is end\n",getpid());
	return 0;
}
