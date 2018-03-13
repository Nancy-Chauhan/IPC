#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
void *func(void*);
void *d;
int main()
{
	int a,i;
	a=2;
	d=(void*)malloc(sizeof(void));
	pthread_t ptr;
	void *s;
	printf("pthread pid=%d\n",getpid());
//	ptr=(int*)malloc(sizeof(int));
	for(i=0;i<4;i++)
	{
	//	printf("hello %d\n",i);	
		pthread_create(&ptr,NULL,func,(void*) a);
		pthread_join(ptr,&s);
		printf("%s\n",(char*)s);
		d++;
	}
		printf("hello\n");	
		printf("size of pthread=%d\n",sizeof(pthread_t));	
		printf("size of pthread=%d\n",ptr);	
		printf("size of pthread=%d\n",&ptr);	
}

void *func(void* p)
{
	int *a;
	a=(int*)p;
	printf("this is a thread =%d\n",a);
	printf("hello thread%d\n",a);	
	printf("pthread pid=%d\n",getpid());
	pthread_exit("bbbyyye thread\n");
}
