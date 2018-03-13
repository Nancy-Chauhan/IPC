#include"header.h"
#include"ds.h"
#include"decleration.h"
int key;
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
	int key;
	void *shared=(void*)0;
	void *memory=(void*)0;
//	sem();
//	set_val();
//	sem_p();
//	p.sa_handler=def;
//	sigemptyset(&p.sa_mask);
//	p.sa_flags=0;
	printf("rec1 with pid %d: is begin\n",getpid());
	k=shmget((key_t)20,sizeof(Request),0666|IPC_CREAT);
	shared=shmat(k,(void*)0,0);
	r=(Request *)shared;
	r->written=0;
	if(!r->written)	
	{
		r->pid=getpid();
		r->opr='+';
		r->oper1=33;
		r->oper2=12;
		r->written=1;
	printf("count of rec1-->%d\n",k);
	}	
//	sem_v();
//	sigaction(SIGALRM,&p,0);
//	pause();
//	printf("signal is generated\n");
//	if(alarm_sig)
//	{
		l=shmget(21,sizeof(Request*),0666|IPC_CREAT);
		memory=shmat(l,(void*)0,0);
		a=(Request*)memory;
		a->written=0;
		while(!a->written)
		{
			if(a->written)
			{
		
				printf("l-->%d\n",l);
				printf("Result of add-->%d\n",a->result);
			}
		}
		a->written=0;
		printf("count of add-->%d\n",count);
//	}
	printf("rec1 with pid %d: is end\n",getpid());
//	del_val();
	return 0;
}
int sem()
{
	key=semget((key_t)123,1,0777|IPC_CREAT);
	printf("key--->%d\n",key);
}
int set_val()
{
	int i;
	union semun a;
	a.val=1;
	i=semctl(key,0,SETVAL,a);
	printf("key=%d\n",key);
	printf("set value=%d\n",i);
}
int sem_p()
{
	int j;
	struct sembuf b[0];
	b[0].sem_num=0;
	b[0].sem_op=-1;
	b[0].sem_flg=0;
	j=semop(key,b,1);
	printf("key=%d\n",key);
	printf("sem_p=%d\n",j);
}
int sem_v()
{
	int j;
	struct sembuf c[1];
	c[0].sem_num=0;
	c[0].sem_op=1;
	c[0].sem_flg=SEM_UNDO;
	j=semop(key,c,1);
	printf("key=%d\n",key);
	printf("sem_v=%d\n",j);
}
int del_val()
{
	int j;
	union semun a;
	struct sembuf b;
	j=semctl(key,0,IPC_RMID,a);
	printf("key=%d\n",key);
	printf("del_val=%d\n",j);
}
