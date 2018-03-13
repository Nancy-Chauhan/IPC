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
	int rfd,i,j,k,wfd,fret,rfd1,count,wfd2,z,p,n;
	char s[4],t[4],u[4],v[4];
	char *argv[2];
	Request d,e;
	printf("Pid :%d server is begin\n",getpid());
	init=initialisation;
	(*init)();
	sem();
	set_val();
	for(;;)
	{
		count=msgget(11,0666|IPC_CREAT);
		i=msgget(12,0666|IPC_CREAT);
		k=msgget(14,0666|IPC_CREAT);
		rfd=msgrcv(count,&d,sizeof(Request),0,0);
		printf("count---->%d\n",count);
		printf("rfd---->%d\n",rfd);
		printf("opr---->%d\n",d.oper1);
		printf("opr---->%d\n",d.oper2);
		switch(d.opr)
		{
			case '+':
				printf("opr in case----%c\n",d.opr);
				fret=fork();
				printf("fret----%d\n",fret);
				msgsnd(i,&d,sizeof(Request),0);
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
				printf("opr in case---->%c\n",d.opr);
				msgsnd(i,&d,sizeof(Request),0); 
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
				printf("opr in case----%c\n",d.opr);
				msgsnd(i,&d,sizeof(Request),0); 
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
		msgsnd(k,&e,sizeof(Request),0); 
		printf("rfd1---->%d\n",e.result);
		printf("count---->%d\n",count);
		printf("result to rec---->%d\n",e.result);
		printf("k---->%d\n",k);
		z=0;
		z++;
		printf("z------------------------------------------->%d\n\n",z);
	}
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
