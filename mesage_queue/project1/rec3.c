#include"header.h"
#include"ds.h"
#include"decleration.h"
int key;
int main()
{
	int wfd,rfd,count,l,k;
	Request r,a;
	struct sigaction p;
	p.sa_handler=def;
	sigemptyset(&p.sa_mask);
	p.sa_flags=0;
	printf("rec3 with pid %d: is begin\n",getpid());
	l=msgget(11,0666|IPC_CREAT);
//	sem();
//	set_val();
//	sem_p();
	r.pid=getpid();
	r.opr='*';
	r.oper1=53;
	r.oper2=22;
	msgsnd(l,&r,sizeof(Request),0);
//	sem_v();
//	sigaction(SIGALRM,&p,0);
//	pause();
//	printf("signal is generated\n");
//	if(alarm_sig)
	{
		k=msgget(14,0666|IPC_CREAT);
		msgrcv(k,&a,sizeof(Request),0,0);
	}
	printf("result mult-->%d\n",a.result);
	printf("count mult-->%d\n",count);
	printf("rec3 with pid %d: is end\n",getpid());
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
}
int set_val()
{
	union semun a;
	a.val=1;
	semctl(key,0,SETVAL,a);
}
int sem_p()
{
	struct sembuf b[1];
	b[0].sem_num=0;
	b[0].sem_op=1;
	b[0].sem_flg=SEM_UNDO;
	semop(key,b,1);
}
int sem_v()
{
	struct sembuf b[1];
	b[0].sem_num=0;
	b[0].sem_op=-1;
	b[0].sem_flg=SEM_UNDO;
	semop(key,b,1);
}
int del_val()
{
	union semun a;
	semctl(key,0,IPC_RMID,a);
}
