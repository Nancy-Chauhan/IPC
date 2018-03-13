#include"header.h"
#include"ds.h"
#include"decleration.h"
int main()
{
	int wfd,rfd,count;
	Request r;
	Result a;
	printf("rec1 with pid %d: is begin\n",getpid());
	r.pid=getpid();
	r.opr='+';
	r.oper1=33;
	r.oper2=12;
	wfd=open("fifo1",O_WRONLY);
	printf("wfd of rec1-->%d\n",wfd);
	write(wfd,&r,sizeof(Request));
	close(wfd);
	rfd=open("fifo4",O_RDONLY);
	count=read(rfd,&a,sizeof(Result));
	close(rfd);
	printf("rfd of rec1-->%d\n",rfd);
	printf("Result of add-->%d\n",a.result);
	printf("count of add-->%d\n",count);
	printf("rec1 with pid %d: is end\n",getpid());
	return 0;
}
