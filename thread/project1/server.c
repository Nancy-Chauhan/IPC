#include"header.h"
#include"ds.h"
#include"decleration.h"
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
//	while(1)
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
	int z=0;
	void* shared=(void*)0;
	Request m,e,*zz;
	pthread_t p;
	union semun b,h;
	b.val=1;
	h.val=1;
//	zz=(Request*)malloc(sizeof(Request)*10);
	i=msgget(12,0666|IPC_CREAT);
	printf("i---->%d\n",i);
	shmid=semget((key_t)123,1,0666|IPC_CREAT);
	z=semctl(shmid,0,SETVAL,b);
//	printf("shmid return value is %d\n",shmid);
//	printf("semctl return value is %d\n",z);
	shmid=semget((key_t)321,1,0666|IPC_CREAT);
	z=semctl(shmid,0,SETVAL,h);
//	printf("shmid return value is %d\n",shmid);
//	printf("semctl return value is %d\n",z);
	sem_init(&a,0,1);
	while(1)
	{
		sret=sem_wait(&a);	
		msgrcv(i,&m,sizeof(Request),0,0); 
//		printf("sret---->%d\n",sret);
		printf("write---->%d\n",m.oper1);
		printf("write---->%d\n",m.oper2);
		if(m.written)
		{	
			m.written=0;
			shmid1=shmget(20,sizeof(Request),0666|IPC_CREAT);
			shared=shmat(shmid1,(void*)0,0);
			printf("size of zz %d\n",sizeof(zz));
			zz=(Request *)shared;
			printf("size of zz %d\n",sizeof(zz));
			printf("size of zz->oper1 %d\n",sizeof(zz->oper1));
			printf("size of zz->ope2 %d\n",sizeof(zz->oper2));
			printf("size of zz->opr %d\n",sizeof(zz->opr));
			zz->oper1=m.oper1;
			printf("shared\n");
			zz->oper2=m.oper2;
			zz->opr=m.opr;
			printf("shared\n");
			zz->pid=m.pid;
			zz->type=m.type;
			printf("opr---->%d\n",zz->oper1);
			printf("opr---->%d\n",zz->oper2);
			printf("opr---->%c\n",zz->opr);
			switch(zz->opr)
			{
//				printf("j---->%d\n",j);
				case '+':
				fret=fork();
//				printf("fret--->%d\n",fret);
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
			sem_post(&a);	
			pthread_create(&p,&attr,thread,0);
			pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
			printf("z------------------------------------------->%d\n\n",z);
			z++;
		}
	}
//	return 0;
}
void* thread(void* y)
{
	int i,j,fret,p,n,shmid,kret,sret;
	union semun aa;
	Request d,*e,l,*m;
	m=(Request *)y;
	e=(Request*)malloc(sizeof(Request));
	//	l=(Request*)malloc(sizeof(Request));
	void *memory=(void*)0;
	n=shmget(22 , sizeof(Request), 0666|IPC_CREAT); 
	memory=shmat(n,(void*)0,0);
	e=(Request *)memory;
	e->written=0;
	sem_init(&a,0,1);
	sret=sem_wait(&a);
	if(sret==-1)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}	
	while( e->written == 0 )
	{
		e->written=1;
		l.result=e->result;
		l.pid=e->pid;
		l.type=e->type;
		printf("result to rec---->%d\n",l.result);
	}		
	j=msgget(13,0666|IPC_CREAT);
	printf("j---->%d\n",j);
//	kret=kill(l.pid,SIGALRM);
	p=msgsnd(j,&l,sizeof(Request),0); 
	if(p==-1)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}	
	l.written=0;
	printf("ret of rslt send =%d\n",p);
//	printf("kill return =%d\n",kret);
//	printf("result in server---->%d\n",l.result);
//	printf("pid of rec---->%d\n",e->pid);
//	printf("p---->%d\n",p);
	shmdt(memory);
	sem_post(&a);	
	printf("Pid :%d server is end\n",getpid());
	//pthread_exit("result of requestig client is given");
	//return 0;
}
