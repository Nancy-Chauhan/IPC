#include"header.h"
#include"ds.h"
#include"decleration.h"
int main()
{
	int a,rfd,b,wfd,count,k,l;
	Request *r,*c;
	void *shared=(void*)0;
	void *memory=(void*)0;
	printf("%d: pc2 is begin\n",getpid());
	k=shmget((key_t)20,sizeof(Request),0666|IPC_CREAT);
	shared=shmat(k,(void*)0,0);
	r=(Request *)shared;
	l=shmget(22,sizeof(Request),0666|IPC_CREAT);
	memory=shmat(l,(void*)0,0);
	c=(Request*)memory;
	a=r->oper1;
	b=r->oper2;
	c->pid=r->pid;
	c->type=r->type;
	c->result=a-b;
	printf("a=%d\n",a);
	printf("b=%d\n",b);
	printf("result of pc2-->%d\n",c->result);
	printf("result of pc2 with pid-->%d\n",c->pid);
printf("%d: is end\n",getpid());
return 0;
}
