#include"header.h"
#include"decleration.h"
int initialisation()
{
	int a;
	printf("%s: is begin\n",__func__);
	a=msgget((key_t)12,0666|IPC_CREAT);
	if(a==-1)
	{
		fprintf(stderr,"fifo is not make\n",mkfifo);
		exit(EXIT_FAILURE);
	}
	a=msgget((key_t)13,0666|IPC_CREAT);
	if(a==-1)
	{
		fprintf(stderr,"fifo is not make\n",mkfifo);
		exit(EXIT_FAILURE);
	}
	a=msgget((key_t)14,0666|IPC_CREAT);
	if(a==-1)
	{
		fprintf(stderr,"fifo is not make\n",mkfifo);
		exit(EXIT_FAILURE);
	}
//	a=msgget((key_t)11,0666|IPC_CREAT);
	if(a==-1)
	{
		fprintf(stderr,"fifo is not make\n",mkfifo);
//		exit(EXIT_FAILURE);
	}
	printf("%s: is end\n",__func__);
}
