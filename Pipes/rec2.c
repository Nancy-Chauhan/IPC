#include"header.h"
#include"decleration.h"
#include"request.h"
int main(int argc,char *argv[])
{
	int wfd,count=0,rfd1,add;
	char q[8];
	Request r;
	struct sigaction p;
        p.sa_handler=def;
        sigemptyset(&p.sa_mask);
        p.sa_flags=0;

	printf("%d: %s is begin\n",getpid(),__FILE__);	
	wfd=atoi(argv[1]);
	printf("Enter the first values\n");
	scanf("%d",&r.opr1);
	printf("Enter any one operation('+','-','*','/')\n");
	scanf(" %c",&r.opt);
	printf("Enter the second values\n");
	scanf("%d",&r.opr2);
	r.pid=getpid();
	count=write(wfd,&r,sizeof(Request));
	printf("write=%d\n",count);
	rfd1=atoi(argv[2]);
	sigaction(SIGALRM,&p,0);
	pause();
	if(alarm_sig)
	{
		count=read(rfd1,&add,sizeof(int));
		printf("Output rec2------------>>%d\n",add);
	}	
	printf("%d: %s is end\n",getpid(),__FILE__);	
}
