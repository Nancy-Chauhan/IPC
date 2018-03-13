#include"header.h"
#include"decleration.h"
#include"request.h"
int main()
{
	int  *pipes,wfd,rfd,rfd1,wfd1,rfd2,wfd2,i,j;
	int  fret,count,exe[4];
	char rres[4],wres[4],q[4],s[4],t[4],wrres[4],u[4];
	char *argv[4],frqt,*argv1[5],*argv2[5],a;
	Request req[4];
	printf("%d:- is begin\n",getpid());
	pipes=init();
	rfd =*(pipes+0);
	wfd =*(pipes+1);
	rfd1=*(pipes+2);	
	wfd1=*(pipes+3);	
	rfd2=*(pipes+4);	
	wfd2=*(pipes+5);
	for(i=0;i<3;i++)
	{
		fret=fork();
		switch(fret)
		{
			case -1:
				printf("Error in fork\n");
				exit(EXIT_FAILURE);
			case 0:
				sprintf(wres,"%d",wfd);
				sprintf(rres,"%d",rfd1);
				char *flnm[]={"rec1","rec2","rec3"};
				char *ptnm[]={"./rec1","./rec2","./rec3"};
				argv[0]=flnm[i];
				argv[1]=wres;
				argv[2]=rres;
				argv[3]=NULL;
				execv(ptnm[i],argv);
				break;
			default:
				count=read(rfd,&req[i],sizeof(Request));
				printf("read=%d\n",count);
			printf("pid--->%d\n",req[i].pid);
		}
	}
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
				argv2[1]=wrres;
				argv2[2]=q;
				argv2[3]=s;
				argv2[4]=t;
				argv2[5]=NULL;
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
				count=read(rfd2,&exe[j],sizeof(int));
				printf("read--->%d\n",count);
				break;
		}
	}
	for(i=0;i<3;i++)
	{
		count=write(wfd1,&exe[i],sizeof(int));
		printf("write--->%d\n",count);
		kill(req[i].pid,SIGALRM);	
		printf("pid--->%d\n",req[i].pid);
	}
	printf("%d: is end\n",getpid());
}
