#include"header.h"
#include"decleration.h"
#include"request.h"
#define FIFO "fifo%d"
int main()
{
	int  *pipes,wfd,rfd,rfd1,wfd1,rfd2,wfd2,i,j;
	int  fret,count;
	int  a,b,c,d,e;
	char buff1[100],buff2[100],buff3[100];
	char rres[4],wres[4],q[4],s[4],t[4],wrres[4],u[4],v[4],z[4];
	char *argv[6],frqt,*argv1[5],*argv2[7];
	Request req[3];
	Request exe[4];
	printf("%d:- is begin\n",getpid());
	pipes=init();
//	rfd =*(pipes+0);
//	wfd =*(pipes+1);
//	rfd1=*(pipes+2);	
//	wfd1=*(pipes+3);	
	rfd2=*(pipes+4);	
	wfd2=*(pipes+5);
	mkfifo("myfile",0666);
	a=open("myfile",O_RDONLY);
	for(i=0;i<3;i++)
	{
		read(a,&req[i],sizeof(Request));
		printf("read pid--->%d\n",req[i].pid);
		printf("read pid--->%d\n",req[i].opr1);
		printf("read pid--->%c\n",req[i].opt);
		printf("read pid--->%d\n",req[i].opr2);
	}	
	unlink("myfile");
	for(j=0;j<3;j++)
	{
		frqt=fork();
		switch(frqt)
		{
			case -1:
				printf("Error in fork\n");
				exit(EXIT_FAILURE);
			case 0:
				sprintf(wrres,"%d",wfd2);
				sprintf(s,"%d",req[j].opr1);
				sprintf(q,"%d",req[j].opt);
				sprintf(t,"%d",req[j].opr2);
				sprintf(v,"%d",req[j].pid);
				argv2[1]=wrres;
				argv2[2]=q;
				argv2[3]=s;
				argv2[4]=t;
				argv2[5]=v;
				argv2[6]=NULL;
				if((req[j].opt) =='+')
				{
					argv2[0]="add";
					execv("./add",argv2);
					break;
				}
				if((req[j].opt) =='-')
				{
					argv2[0]="sub";
					execv("./sub",argv2);
					break;
				}
				if((req[j].opt) =='*')
				{
					argv2[0]="mul";
					execv("./mul",argv2);
					break;
				}
				break;
			default:
				count=read(rfd2,&exe[j],sizeof(Request));
				printf("read--->%d\n",count);
				break;
		}
	}
	for(i=0;i<3;i++)
	{
		sprintf(z,FIFO,exe[i].pid);
		printf("fifo--->%s\n",z);
		printf("read pid--->%d\n",exe[i].pid);
		printf("read pid--->%d\n",exe[i].result);
		wfd1=open(z,O_WRONLY);	
		sleep(2);
		count=write(wfd1,&exe[i].result,sizeof(int));
		printf("read pid--->%d\n",wfd1);
		unlink(z);
	}
	printf("%d: is end\n",getpid());
}
