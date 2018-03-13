#include"header.h"
#include"decleration.h"
#include"request.h"
int main(int argc,char *argv[])
{
	int wfd,count,a,b,c,sub;
	Request d;
	printf("%d: %s is begin\n",getpid(),__FILE__);	
	wfd=atoi(argv[1]);
	b=atoi(argv[3]);
	c=atoi(argv[4]);
	d.pid=atoi(argv[5]);
	d.result=b-c;
	count=write(wfd,&d,sizeof(Request));
	printf("count-->%d\n",count);
	printf("%d: %s is end\n",getpid(),__FILE__);	
}
