#include"header.h"
#include"shm.h"
int main()
{
	int shmid,a=1;
	char buf[100];
	struct sm *b;
	void *shared=(void*)0;
	shmid=shmget(2,sizeof(struct sm),0666|IPC_CREAT);
	shared=shmat(shmid,(void*)0,0);
	b=(struct sm *)shared;
	b->written=0;
	while(a)
	{
		if(!b->written)
		{
			printf("enter your text\n");
			fgets(b->text,100,stdin);
		//	strcpy(b->text,buf);
			b->written=1;
		}
	}
	shmdt(shared);
}
