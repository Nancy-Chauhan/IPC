#include"header.h"
#include"decleration.h"
#include"request.h"
int main(int argc,char *argv[])
{
	int wfd,count,add,a,b,c;
	Request r;
	printf("%d: %s is begin\n",getpid(),__FILE__);	
	b=atoi(argv[3]);
	c=atoi(argv[4]);
	r.pid=atoi(argv[5]);
	wfd=atoi(argv[1]);
	r.result=b*c;
	count=write(wfd,&r,sizeof(Request));
	printf("write-->=%d\n",count);
	printf("%d: %s is end\n",getpid(),__FILE__);	
}
