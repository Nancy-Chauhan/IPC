#include"header.h"
#include"ds.h"
#include"decleration.h"
int main()
{
	int a,rfd,b,wfd,count;
	Request r;
	Result c;
	printf("%d: is pc3 begin\n",getpid());
	rfd=open("fifo2",O_RDONLY);
	read(rfd,&r,sizeof(Request));
	close(rfd);
	a=r.oper1;
	b=r.oper2;
	c.pid=r.pid;
	c.result=a*b;
	printf("aa--->%d\n",a);
	printf("bb--->%d\n",b);
	printf("result of pc3-->%d\n",c.result);
	wfd=open("fifo3",O_WRONLY);
	count=write(wfd,&c,sizeof(Result));
	printf("count-----=%d\n",count);
	close(wfd);
	printf("%d: is end\n",getpid());
	return 0;
}
