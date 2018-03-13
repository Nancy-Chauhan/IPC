#include"header.h"
#include"shm.h"

int main()
{
	int shmid,a=1;
	struct sm *shd;
	void *shared=(void*)0;
	shmid=shmget(2,sizeof(struct sm),0666|IPC_CREAT);
	shared=shmat(shmid,(void*)0,0);
	shd=(struct sm*)shared;
	shd->written=0;	
	while(a)
	{
		if(shd->written)
		{
			sleep(1);
			printf("you: %s\n",shd->text);
			shd->written=0;	
		}
	}
	shmdt(shared);
}
