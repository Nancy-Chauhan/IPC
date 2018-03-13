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
	wfd=atoi(argv[1]);
	add=b*c;
	count=write(wfd,&add,sizeof(int));
	printf("write-->=%d\n",count);
	printf("%d: %s is end\n",getpid(),__FILE__);	
}
