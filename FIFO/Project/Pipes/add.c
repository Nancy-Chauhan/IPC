#include"header.h"
#include"decleration.h"
#include"request.h"
int main(int argc,char *argv[])
{
	int wfd,count,add,a,b,c;
	Request d;
	printf("%d: %s is begin\n",getpid(),__FILE__);	
	b=atoi(argv[3]);
	c=atoi(argv[4]);
	d.pid=atoi(argv[5]);
	printf("pid=%d\n",d.pid);	
	wfd=atoi(argv[1]);
	d.result=b+c;
	printf("pid=%d\n",b);	
	printf("pid=%d\n",c);	
	printf("pid=%d\n",d.result);	
	count=write(wfd,&d,sizeof(Request));
	printf("write=%d\n",count);	
	printf("%d: is end\n",getpid(),__FILE__);	
}
