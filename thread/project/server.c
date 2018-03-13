#include"header.h"
#include"ds.h"
#include"decleration.h"
int z=0;
sem_t a,c;
int shmid,shmid1;
void* thread(void *);
void* thread1(void *);
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};
void dd(int sig)
{
	semctl(shmid,0,IPC_RMID);
	sem_destroy(&a);
}
pthread_attr_t attr;
int main()
{
	pthread_attr_init(&attr);
	pthread_t p;
	printf("Pid :%d server is begin\n",getpid());
	while(1)
	{
	pthread_create(&p,&attr,thread1,0);
	pthread_join(p,NULL);
	}
	//	printf("Pid :%d server is end\n",getpid());
}
void* thread1(void* y)
{
	int i,j,fret,shmid,shmid1,n,sret;
	char *argv[2];
	void* shared=(void*)0;
	Request *m,e;
	pthread_t p;
	union semun b;
	b.val=1;
	shmid=semget((key_t)123,1,0666|IPC_CREAT);
	z=semctl(shmid,0,SETVAL,b);
	printf("semctl return value is %d\n",shmid);
	sem_init(&a,0,1);
	sret=sem_wait(&a);	
	printf("sret---->%d\n",sret);
	shmid1=shmget(20,sizeof(Request),0666|IPC_CREAT);
	shared=shmat(shmid1,(void*)0,0);
	m=(Request *)shared;
	while(1)
	{
		if(m->written)
		{	
			m->written=0;
			printf("opr---->%d\n",m->oper1);
			printf("opr---->%d\n",m->oper2);
			printf("opr---->%c\n",m->opr);
			printf("pid---->%d\n",m->pid);
			i=msgget(12,0666|IPC_CREAT);
			printf("i---->%d\n",i);
			msgsnd(i,m,sizeof(Request),0); 
			printf("pid----%d\n",m->pid);
			switch(m->opr)
			{
				printf("j---->%d\n",j);
				case '+':
				fret=fork();
				printf("fret--->%d\n",fret);
				switch(fret)
				{
					case 0:
						argv[0]="pc1";
						argv[1]=NULL;
						execv("./pc1",argv); 
					default:
						wait(&n);
				}
				break;
				case '-':
				fret=fork();
				switch(fret)
				{
					case 0:
						argv[0]="pc2";
						argv[1]=NULL;
						execv("./pc2",argv); 
						break;
					default: 
						wait(&n);
				}
				break;
				case '*':
				fret=fork();
				switch(fret)
				{
					case 0:
						argv[0]="pc3";
						argv[1]=NULL;
						execv("./pc3",argv); 
						break;
					default: 
						wait(&n);
				}
				break;
				default:
				printf("sorry ur program is not properly work\n");
				break;
			}
			pthread_create(&p,&attr,thread,&e);
			pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
			sem_post(&a);	
		}
	}
//	pthread_exit("result of requestig client is given");
	return 0;
}
void* thread(void* y)
{
	int i,j,fret,p,n,shmid,kret,sret;
	union semun aa;
	Request d,e,*l,*m;
	m=(Request *)y;
	void *memory=(void*)0;
	n=shmget(22 , sizeof(Request), 0666|IPC_CREAT); 
	memory=shmat(n,(void*)0,0);
	l=(Request *)memory;
	l->written=0;
	printf("j---->%d\n",j);
	j=msgget(13,0666|IPC_CREAT);
	printf("j---->%d\n",j);
	p=msgrcv(j,&e,sizeof(Request),0,0); 
	printf("result in server---->%d\n",e.result);
	printf("pid of rec---->%d\n",e.pid);
	printf("p---->%d\n",p);
	printf("kill return =%d\n",kret);
	while( l->written == 0 )
	{
		l->written=1;
		l->result=e.result;
		printf("result to rec---->%d\n",l->result);
	}		
	kret=kill(e.pid,SIGALRM);
	shmdt(memory);
	printf("z------------------------------------------->%d\n\n",z);
	z++;
	printf("Pid :%d server is end\n",getpid());
	return 0;
}
