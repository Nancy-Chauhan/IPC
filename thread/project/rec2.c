#include"header.h"
#include"ds.h"
#include"decleration.h"
int key;
int tea;
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};
int main()
{
	int wfd,rfd,count,l,m,n,i;
	Request *r,*a;
	long k;
	struct sigaction p;
	void *shared=(void*)0;
	void *memory=(void*)0;
	sem();
	p.sa_handler=def;
	printf("rec2 with pid %d: is begin\n",getpid());
	sigemptyset(&p.sa_mask);
	p.sa_flags=0;
	k=shmget((key_t)20,sizeof(Request),0666|IPC_CREAT);
	shared=shmat(k,(void*)0,0);
	r=(Request *)shared;
	sem_p();
	r->written=0;
	if(!r->written)	
	{
		r->written=1;
		r->pid=getpid();
		r->opr='-';
		r->oper1=33;
		r->oper2=12;
		printf("count of rec2-->%d\n",k);
	}	
	sem_v();
	sigaction(SIGALRM,&p,0);
	pause();
	if(alarm_sig)
	{
		l=shmget(22,sizeof(Request),0666|IPC_CREAT);
		memory=shmat(l,(void*)0,0);
		a=(Request*)memory;
			if(a->written ==1)
			{	
				printf("l-->%d\n",l);
				printf("Result of sub-->%d\n",a->result);
			}
	}
	printf("rec2 with pid %d: is end\n",getpid());
	exit(EXIT_SUCCESS);
	return 0;
}
int sem()
{
	key=semget((key_t)123,1,0666|IPC_CREAT);
	tea=semget((key_t)12,1,0666|IPC_CREAT);
}
int sem_p()
{
	int j;
	struct sembuf b[0];
	b[0].sem_num=0;
	b[0].sem_op=-1;
	b[0].sem_flg=SEM_UNDO;
	j=semop(key,b,1);
	//	printf("key=%d\n",key);
	//	printf("sem_p=%d\n",j);
}
int sem_v()
{
	int j;
	struct sembuf c[1];
	c[0].sem_num=0;
	c[0].sem_op=1;
	c[0].sem_flg=SEM_UNDO;
	j=semop(key,c,1);
	//	printf("key=%d\n",key);
	//	printf("sem_v=%d\n",j);
}
int sem_p1()
{
	int j;
	struct sembuf b[0];
	b[0].sem_num=0;
	b[0].sem_op=-1;
	b[0].sem_flg=SEM_UNDO;
	j=semop(tea,b,1);
	//	printf("key=%d\n",tea);
	//	printf("sem_p=%d\n",j);
}
int sem_v1()
{
	int j;
	struct sembuf c[1];
	c[0].sem_num=0;
	c[0].sem_op=1;
	c[0].sem_flg=SEM_UNDO;
	j=semop(tea,c,1);
	//	printf("key=%d\n",tea);
	//	printf("sem_v=%d\n",j);
}
int del_val()
{
	int j;
	union semun a;
	struct sembuf b;
	j=semctl(key,0,IPC_RMID,a);
	j=semctl(tea,0,IPC_RMID,a);
	//	printf("key=%d\n",key);
	//	printf("del_val=%d\n",j);
}
