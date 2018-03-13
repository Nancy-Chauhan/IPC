#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<signal.h>
#include<fcntl.h>
void *func(void*);
void handlerfunc(int);
int i;
pthread_t ptr[10];
int main()
{
	int a;
	int b;
	printf("pthread pid=%d\n",getpid());
	signal(SIGINT,handlerfunc);	
	for(i=0;i<10;i++)
	{
		sleep(1);
		a=pthread_create(&ptr[i],NULL,func,&i);
		printf("Thread are--> =%d\n",i);
	}
	while(1)
	{
		sleep(1);
		printf("main func\n");
	}
	printf("size of pthread=%d\n",sizeof(pthread_t));	
	printf("return of pthread=%d\n",a);	
	printf("size of pthread=%d\n",&ptr);
	for(i=0;i<10;i++)
	{
		pthread_join(ptr[i],NULL);
	}
}
void *func(void* p)
{
	int a;
	a=*(int*)p;
	while(1)
	{
		sleep(1);
		printf("this is a thread =%d\n",a);
		signal(SIGINT,handlerfunc);	
	}
	printf("hello thread%d\n",a);	
	printf("pthread pid=%d\n",getpid());
	pthread_exit("bye");
}
void handlerfunc(int a)
{
	printf("signal is invoke %d\n",a);
	pthread_exit("bbye");
}
