#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
	int a;
	a=mkfifo("MYFIFO",0777);
	printf("FIFO=%d\n",a);
}
