#include"header.h"
#include"decleration.h"
int *init()
{
	int *pipes,i;

	printf("%s: is begin\n",__func__);
	pipes=(int*)malloc(sizeof(int)*6);
	for(i=0;i<3;i++)
	{
		pipe(pipes+i*2);
	}
	printf("%s: is end\n",__func__);
	return pipes;
}
