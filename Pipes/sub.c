#include"header.h"
#include"decleration.h"
#include"request.h"
int main(int argc,char *argv[])
{
	int wfd,count,a,b,c,sub;
	printf("%d: %s is begin\n",getpid(),__FILE__);	
	wfd=atoi(argv[1]);
	b=atoi(argv[3]);
	c=atoi(argv[4]);
	sub=b-c;
	count=write(wfd,&sub,sizeof(int));
	printf("count-->%d\n",count);
	printf("%d: %s is end\n",getpid(),__FILE__);	
}
