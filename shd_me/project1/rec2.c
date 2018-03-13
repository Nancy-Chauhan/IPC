#include"header.h"
#include"ds.h"
#include"decleration.h"
int key;
int main()
{
	int wfd,rfd,count,k;
	Request *r,*a;
	struct sigaction p;
	long l;
	void* shared=(void*)0;
	void* memory=(void*)0;
	p.sa_handler=def;
	sigemptyset(&p.sa_mask);
	p.sa_flags=0;
	printf("rec2 with pid %d: is begin\n",getpid());
	l=shmget(20,sizeof(Request),0666|IPC_CREAT);
//	sem();
//	set_val();
//	sem_p();
	shared=shmat(l,(void*)0,0);
	r=(Request *)shared;
	r->written=0;
	if(!r->written)
	{
		r->pid=getpid();
		r->opr='-';
		r->oper1=42;
		r->oper2=16;
		r->written=1;
	}
//	sem_v();
//	sigaction(SIGALRM,&p,0);
//	pause();
//	printf("signal is generated\n");
//	if(alarm_sig)
		k=shmget(21,sizeof(Request),0666|IPC_CREAT);
		memory=shmat(k,(void*)0,0);
		a=(Request*)memory;
		a->written=0;
		while(!a->written)
		{
			if(a->written)
			{
				printf("result sub--->%d\n",a->result);
			}
		}
		a->written=0;
	printf("rec2 with pid %d: is end\n",getpid());
	close(rfd);
	return 0;
}
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};
int sem()
{
	key=semget((key_t)123,1,0666|IPC_CREAT);
	printf("key=%d\n",key);
}
int set_val()
{
	union semun a;
	a.val=1;
	semctl(key,0,SETVAL,a);
	printf("key=%d\n",key);
}
int sem_p()
{
	struct sembuf b[1];
	b[0].sem_num=0;
	b[0].sem_op=1;
	b[0].sem_flg=SEM_UNDO;
	semop(key,b,1);
	printf("key=%d\n",key);
}
int sem_v()
{
	struct sembuf b[1];
	b[0].sem_num=0;
	b[0].sem_op=-1;
	b[0].sem_flg=SEM_UNDO;
	semop(key,b,1);
	printf("key=%d\n",key);
}
int del_val()
{
	union semun a;
	semctl(key,0,IPC_RMID,a);
	printf("key=%d\n",key);
}
