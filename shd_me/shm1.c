#include"header.h"
#include"shm.h"

int main()
{
	int an=1;
	void *shared_memory=(void *)0;
	struct sm *shared;
	int shmid;
	shmid=shmget(1234,sizeof(struct sm),0666|IPC_CREAT);
	if(shmid==-1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	shared_memory=shmat(shmid,(void *)0,0);
	if(shared_memory == (void *)-1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	shared=(struct sm*)shared_memory;
	shared->written=0;
	while(an)
	{
		if(shared->written)
		{
			printf("YOU :%s",shared->text);
			sleep(rand() %4);	
			shared->written=0;
			if(strncmp(shared->text,"end",3)==0)
				an=0;	
		}
	}
	if(shmdt(shared)==-1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	if(shmctl(shmid,IPC_RMID,0)==-1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
