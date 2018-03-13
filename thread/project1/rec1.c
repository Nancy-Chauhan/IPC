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
	r=(Request*)malloc(sizeof(Request));
	a=(Request*)malloc(sizeof(Request));
	printf("rec1 with pid %d: is begin\n",getpid());
	sem();
	p.sa_handler=def;
	sigemptyset(&p.sa_mask);
	p.sa_flags=0;
	sem_p();
	r->written=0;
	if(!r->written)	
	{
		r->written=1;
		r->pid=getpid();
		r->opr='+';
		r->oper1=33;
		r->oper2=12;
		l=msgget(12,0666|IPC_CREAT);
        	count=msgsnd(l,r,sizeof(Request),0);
		printf("retmsgsnd of rec1-->%d\n",count);
	}	
	sem_v();
	sem_p1();
//	sigaction(SIGALRM,&p,0);
//	pause();
//	if(alarm_sig)
	{
		k=msgget(13,0666|IPC_CREAT);
		printf("count  %d \n",k);
	        count=msgrcv(k,a,sizeof(Request),0,0);
		printf("Result of add-->%d\n",a->result);
	}
	printf("rec1 with pid %d: is end\n",getpid());
	sem_v1();
	return 0;
}
int sem()
{
	key=semget((key_t)123,1,0666|IPC_CREAT);
	tea=semget((key_t)321,1,0666|IPC_CREAT);
	printf("key--->%d\n",key);
	printf("tea--->%d\n",tea);
}
int sem_p()
{
	int j;
	struct sembuf b;
	b.sem_num=0;
	b.sem_op=-1;
	b.sem_flg=SEM_UNDO;
	j=semop(key,&b,1);
	printf("key=%d\n",key);
	//	printf("sem_p=%d\n",j);
}
int sem_v()
{
	int j;
	struct sembuf c;
	c.sem_num=0;
	c.sem_op=1;
	c.sem_flg=SEM_UNDO;
	j=semop(key,&c,1);
	//	printf("key=%d\n",key);
	//	printf("sem_v=%d\n",j);
}
int sem_p1()
{
	int j;
	struct sembuf b;
	b.sem_num=0;
	b.sem_op=-1;
	b.sem_flg=SEM_UNDO;
	j=semop(tea,&b,1);
	printf("tea=%d\n",tea);
	//	printf("sem_p=%d\n",j);
}
int sem_v1()
{
	int j;
	struct sembuf c;
	c.sem_num=0;
	c.sem_op=1;
	c.sem_flg=SEM_UNDO;
	j=semop(tea,&c,1);
	//	printf("key=%d\n",key);
	//	printf("sem_v=%d\n",j);
}
int del_val()
{
	int j;
	union semun a;
	j=semctl(key,0,IPC_RMID,a);
	//	printf("key=%d\n",key);
	//	printf("del_val=%d\n",j);
}
