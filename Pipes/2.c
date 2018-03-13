#include<stdio.h>
#include<stdlib.h>

int main(int argc,char* argv[])
{
	int fd,ret,i,byte;
	char rbuff[50];
	printf("%s:is begin\n",__FILE__);
	fd=atoi(argv[1]);
	while(1)
	{
		ret=read(fd,rbuff,50);
		printf("%d: byte read=%d\n",getpid(),ret);
	}
	printf("fd=%d\n",fd);
	printf("%s:is end\n",__FILE__);
}

