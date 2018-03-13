#include"header.h"
#include"ds.h"
#include"decleration.h"
int main()
{
	int a,rfd,b,wfd,count,k,l;
	Request r,c;
	printf("%d: pc1 is begin\n",getpid());
	k=msgget(12,0666|IPC_CREAT);
	count=msgrcv(k,&r,sizeof(Request),0,0);	
	a=r.oper1;
	b=r.oper2;
	c.pid=r.pid;
	c.result=a+b;
	printf("a=%d\n",a);
	printf("b=%d\n",b);
	printf("result of pc1-->%d\n",c.result);
	l=msgget(13,0666|IPC_CREAT);
	count=msgsnd(l,&c,sizeof(Request),0);	
	printf("l-----------=%d\n",l);
	printf("count-----------=%d\n",count);
	printf("%d: is end\n",getpid());
	return 0;
}
