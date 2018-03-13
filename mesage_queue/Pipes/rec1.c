#include"header.h"
#include"decleration.h"
#include"request.h"
#define FIFO "fifo%d"
int main(int argc,char *argv[])
{
	int wfd,count=0,rfd1,add;
	char q[8],z[6];
	Request r;
	printf("%d:%s is begin\n",getpid(),__FILE__);	
	r.pid=getpid();
	r.opt='+';
	r.opr2=33;
	r.opr1=43;
	wfd=open("myfile",O_WRONLY);
	count=write(wfd,&r,sizeof(Request));
	printf("write=%d\n",count);
	sprintf(z,FIFO,getpid());
	printf("z-->%s",z);
	mkfifo(z,0666);
	rfd1=open(z,O_RDONLY);
	sleep(3);
	count=read(rfd1,&add,sizeof(int));
	printf("rfd------------->>>>%d\n",rfd1);
	printf("output rec1------------->>>>%d\n",add);
	printf("%d:%s is end\n",getpid(),__FILE__);	
}
