#include"header.h"
#include"shm.h"
int main()
{
	int r=1;
	void *sh=(void *)0;
	struct sm *share;
	char buffer[BUFSIZ];
	int shmid;
	shmid=shmget(1234,sizeof(struct sm),0666|IPC_CREAT);
	if(shmid==-1)
	{
		perror("shmget");
		exit(EXIT_FAILURE);
	}
	share=shmat(shmid,(void*)0,0);
	if(share==-1)
	{
		perror("share");
		exit(EXIT_FAILURE);
	}
	printf("memory at %X\n",share);
	share=(struct sm*)share;
	while(r)
	{
//		while(share->written ==1)
		{
			sleep(1);
			printf("wait for client\n");
		}
		printf("Enter some text:");
		fgets(buffer,BUFSIZ,stdin);
		strncpy(share->text,buffer,TEXT);
		share->written=1;
		if(strncmp(buffer,"end",3)==0)
			r=0;
	}
	if(shmdt(share)==-1)
	{
		perror("share");
		exit(EXIT_FAILURE);
	}
		exit(EXIT_SUCCESS);
}
