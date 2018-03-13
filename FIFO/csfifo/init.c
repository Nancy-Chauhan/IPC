#include"header.h"
#include"ds.h"
#include"decleration.h"
int initialisation()
{
	int a;
	printf("%s: is begin\n",__func__);
	if(access("fifo1",F_OK)==-1)
	{
		a=mkfifo("fifo1",0666);
		if(a==-1)
		{
			fprintf(stderr,"fifo is not make\n",mkfifo);
			exit(EXIT_FAILURE);
		}
	}
	if(access("fifo2",F_OK)==-1)
	{
		a=mkfifo("fifo2",0666);
		if(a==-1)
		{
			fprintf(stderr,"fifo is not make\n",mkfifo);
			exit(EXIT_FAILURE);
		}
	}
	if(access("fifo3",F_OK)==-1)
	{
		a=mkfifo("fifo3",0666);
		if(a==-1)
		{
			fprintf(stderr,"fifo is not make\n",mkfifo);
			exit(EXIT_FAILURE);
		}
	}
	if(access("fifo4",F_OK)==-1)
	{
		a=mkfifo("fifo4",0666);
		if(a==-1)
		{
			fprintf(stderr,"fifo is not make\n",mkfifo);
			exit(EXIT_FAILURE);
		}
	}
	printf("%s: is end\n",__func__);
}
