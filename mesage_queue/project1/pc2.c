#include"header.h"
#include"ds.h"
#include"decleration.h"
int main()
{
	int a,rfd,b,wfd,count,l,k;
	Request r,c;
	printf("%d: is pc2 begin\n",getpid());
	k=msgget(12,0666|IPC_CREAT);
	count=msgrcv(k,&r,sizeof(Request),0,0);	
	a=r.oper1;
	b=r.oper2;
	c.pid=r.pid;
	c.result=a-b;
	printf("a---->%d\n",a);
	printf("b---->%d\n",b);
	printf("result of pc2-->%d\n",c.result);
	l=msgget(13,0666|IPC_CREAT);
	printf("l---->%d\n",l);
	count=msgsnd(l,&c,sizeof(Request),0);	
	printf("%d: is end\n",getpid());
	return 0;
}
