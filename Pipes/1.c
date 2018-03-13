#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
int main()
{
	int ret,arr[3],fret,len,i=0,byte;
	char buff[]={"hello,how r u ???"};
	char sfd[4];
	char wbuff[4096];
	printf("%s: is begin\n",__FILE__);
	pipe(arr);
	printf("ar[0]=%d\n",arr[0]);
	printf("ar[1]=%d\n",arr[1]);
	len=strlen(buff);
	write(arr[1],wbuff,len);
	i=1024;
	fret=fork();
	switch(fret)
	{
		case -1:
			printf("error in fork call\n");
			break;
		case 0:
			printf("pid :%d child pid %d\n",getpid(),getppid());
			sprintf(sfd,"%d",arr[0]);
			execl("./2","2",sfd,NULL);
			break;
		default:
			printf("pid :%d parents pid %d\n",getpid(),getppid());
	}
//	while(1)
//	{
		len=write(arr[1],wbuff,100);
		close(arr[0]);
		close(arr[1]);
		printf("%d: byte write=%d\n",getpid(),len);
		//close(arr[1]);
		//sleep(10);
//		break;
//	}
	printf("%s: is end\n",__FILE__);
}
	
