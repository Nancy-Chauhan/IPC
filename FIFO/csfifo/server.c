#include"header.h"
#include"ds.h"
#include"decleration.h"
int main()
{
	int a,rfd,i,wfd,fret,rfd1,count,wfd2;
	char *argv[2];
	char s[4],t[4],u[4],v[4];
	Request r;
	Request d[3];
	Result e[3];
	printf("Pid :%d server is begin\n",getpid());
	init=initialisation;
	(*init)();
	
	for(i=0;i<3;i++)
	{
		printf("waiting for Read\n");
		rfd=open("fifo1",O_RDONLY);
		printf("rfd=%d\n",rfd);
		read(rfd,&d[i],sizeof(Request));
		close(rfd);
		printf("pid---->%d\n",d[i].pid);
		printf("opr---->%c\n",d[i].opr);
		printf("oper1---->%d\n",d[i].oper1);
		printf("oper2---->%d\n",d[i].oper2);
	}
	for(i=0;i<3;i++)
	{
		printf("opr in loop----%c\n",d[i].opr);
		switch(d[i].opr)
		{
			case '+':
				printf("opr in case----%c\n",d[i].opr);
				fret=fork();
				switch(fret)
				{
					case 0:
						printf("waiting for Read for pc1\n");
						argv[0]="pc1";
						argv[1]=NULL;
						execv("./pc1",argv); 
					default: 
						wfd=open("fifo2",O_WRONLY);
						write(wfd,&d[i],sizeof(Request));
						break;
				}
				break;
			case '-':
				printf("opr in case----%c\n",d[i].opr);
				fret=fork();
				switch(fret)
				{
					case 0:
						printf("waiting for Read for pc2\n");
						argv[0]="pc2";
						argv[1]=NULL;
						execv("./pc2",argv); 
					default: 
						wfd=open("fifo2",O_WRONLY);
						write(wfd,&d[i],sizeof(Request));
						break;
				}
				break;
			case '*':
				printf("opr in case----%c\n",d[i].opr);
				fret=fork();
				switch(fret)
				{
					case 0:
						argv[0]="pc3";
						argv[1]=NULL;
						execv("./pc3",argv); 
					default: 
						printf("waiting for Read for pc3\n");
						wfd=open("fifo2",O_WRONLY);
						write(wfd,&d[i],sizeof(Request));
						break;
				}
			default:
				printf("sorry ur program is not properly working\n");
		}
		printf("waiting for Read for fifo3\n");
		rfd1=open("fifo3",O_RDONLY);
		count=read(rfd1,&e[i],sizeof(Result));			
		printf("rfd1---->%d\n",rfd1);
		printf("count---->%d\n",count);
		printf("pid---->%d\n",e[i].pid);
		printf("result in server---->%d\n",e[i].result);
	}
	for(i=0;i<3;i++)
	{
		wfd2=open("fifo4",O_WRONLY);
		write(wfd2,&e[i],sizeof(Result));
		printf("rfd1---->%d\n",rfd1);
		printf("count---->%d\n",count);
		printf("pid---->%d\n",e[i].pid);
		printf("result---->%d\n",e[i].result);
		close(wfd2);
	}
	unlink("fifo1");
	unlink("fifo2");
	unlink("fifo3");
	unlink("fifo4");
	printf("Pid :%d server is end\n",getpid());
	return 0;
}
