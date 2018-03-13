#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#define FIFO_NAME "fifo"
#define filesize (1020*1020*10)
#define BUFFER_SIZE (1020*4) 
int main()
{
	int ret,pt;
	int byte_sent=0;
	char buff[BUFFER_SIZE+1];
	if(access(FIFO_NAME,F_OK)==-1)
	{
		printf("FIFO is not made yet\n");
		ret=mkfifo(FIFO_NAME,0777);
		if(ret !=0)
		{
			fprintf(stderr,"Fifo is not made %s\n",FIFO_NAME);
			exit(EXIT_FAILURE);
		}
	}
	ret=open(FIFO_NAME,O_RDONLY);
	if(ret ==-1)
	{
		fprintf(stderr,"Fifo is not open in write mode %s\n",FIFO_NAME);
		exit(EXIT_FAILURE);
	}
	printf("reading data is start\n");
		sleep(5);
	while(byte_sent < filesize)
	{
		pt=read(ret,buff,BUFFER_SIZE);
		printf("%s\n",buff);
	}
}
