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
	int i,j,k,fret,count,wfd2,z,p,n,shmid;
	char s[4],t[4],u[4],v[4];
	char *argv[2];
	long a;
	Request d,e,*m,*l;
	void *shared=(void*)0;
	void *memory=(void*)0;
	printf("Pid :%d server is begin\n",getpid());
	init=initialisation;
	(*init)();
	sem();
	set_val();
	shmid=shmget(20,sizeof(Request),0666|IPC_CREAT);
	shared=shmat(shmid,(void*)0,0);
	m=(Request *)shared;
	m->written=0;
	for(z=0;z<3;z++)
	{
		while(!m->written)
		{
			if(m->written)
			{	
				printf("opr---->%d\n",m->oper1);
				printf("opr---->%d\n",m->oper2);
				printf("opr---->%c\n",m->opr);
			}
		}
		i=msgget(12,0666|IPC_CREAT);
		msgsnd(i,m,sizeof(Request),0); 
		switch(m->opr)
		{
			case '+':
				printf("opr in case----%c\n",m->opr);
				fret=fork();
				printf("fret----%d\n",fret);
				switch(fret)
				{
					case 0:
						printf("waiting for Read for pc1\n");
						argv[0]="pc1";
						argv[1]=NULL;
						execv("./pc1",argv); 
					default:
						wait(&n);
						printf("-------------------------------------------------\n");
				}
				break;
			case '-':
				printf("opr in case---->%c\n",m->opr);
				fret=fork();
				switch(fret)
				{
					case 0:
						printf("waiting for Read for pc2\n");
						argv[0]="pc2";
						argv[1]=NULL;
						execv("./pc2",argv); 
						printf("-------------------------------------------------\n");
						break;
					default: 
						wait(&n);
						printf("-------------------------------------------------\n");
				}
				break;
			case '*':
				printf("opr in case----%c\n",m->opr);
				fret=fork();
				switch(fret)
				{
					case 0:
						argv[0]="pc3";
						argv[1]=NULL;
						execv("./pc3",argv); 
						printf("-------------------------------------------------\n");
						break;
					default: 
						wait(&n);
				}
				break;
			default:
				printf("sorry ur program is not properly work\n");
		}
		printf("waiting for Read for fifo3\n");
		j=msgget(13,0666|IPC_CREAT);
		printf("j---->%d\n",j);
		p=msgrcv(j,&e,sizeof(Request),0,0); 
		printf("result in server---->%d\n",e.result);
		printf("p---->%d\n",p);

		//	kill(e.pid,SIGALRM);
		//		sem_p();
		n=shmget(21,sizeof(Request),0666|IPC_CREAT); 
		memory=shmat(n,(void*)0,0);
		l=(Request*)memory;
		m->written=0;
		while(!l->written)
		{
			l->result=e.result;
			l->written=1;
		}		
		printf("rfd1---->%d\n",l->result);
		printf("count---->%d\n",count);
		printf("result to rec---->%d\n",l->result);
		printf("k---->%d\n",k);
		printf("z------------------------------------------->%d\n\n",z);
	}
	shmdt(shared);
	shmdt(memory);
	//		sem_v();
	printf("Pid :%d server is end\n",getpid());
	return 0;
}
int sem()
{
	key=semget((key_t)12,1,0777|IPC_CREAT);
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
