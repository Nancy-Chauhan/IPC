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
	Request *r,a;
	long k;
	struct sigaction p;
	r=(Request*)malloc(sizeof(Request));
	printf("rec3 with pid %d: is begin\n",getpid());
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
		r->opr='*';
		r->oper1=33;
		r->oper2=12;
		l=msgget(12,0666|IPC_CREAT);
        	count=msgsnd(l,r,sizeof(Request),0);
		printf("retmsgsen of rec3-->%d\n",count);
	}	
	sem_v();
	sem_p1();
//	sigaction(SIGALRM,&p,0);
//	pause();
//	if(alarm_sig)
	{
		k=msgget(13,0666|IPC_CREAT);
		printf("retmsg  %d \n",k);
	        count=msgrcv(k,&a,sizeof(Request),0,0);
		printf("Result of mul-->%d\n",a.result);
	}
	sem_v1();
	printf("rec3 with pid %d: is end\n",getpid());
	return 0;
}
int sem()
{
	key=semget((key_t)123,1,0666|IPC_CREAT);
	tea=semget((key_t)321,1,0666|IPC_CREAT);
		printf("key--->%d\n",key);
}
int sem_p()
{
	int j;
	struct sembuf b[0];
	b[0].sem_num=0;
	b[0].sem_op=-1;
	b[0].sem_flg=SEM_UNDO;
	j=semop(key,b,1);
		printf("key=%d\n",key);
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
