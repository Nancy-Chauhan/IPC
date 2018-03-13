#include"header.h"
#include"ds.h"
#include"decleration.h"
int key;
int main()
{
	int wfd,rfd,count;
	Request r;
	Result a;
	struct sigaction p;
	p.sa_handler=def;
	sigemptyset(&p.sa_mask);
	p.sa_flags=0;
	printf("rec2 with pid %d: is begin\n",getpid());
	sem();
	set_val();
	sem_p();
	r.pid=getpid();
	r.opr='-';
	r.oper1=42;
	r.oper2=16;
	msgsnd(11,&r,sizeof(Request),0);
	sem_v();
//	sigaction(SIGALRM,&p,0);
//	pause();
//	printf("signal is generated\n");
//	if(alarm_sig)
	{
		msgrcv(11,&r,sizeof(Result),0);
	}
	printf("result sub--->%d\n",a.result);
	printf("count sub--->%d\n",count);
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
