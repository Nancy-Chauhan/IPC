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
	int rfd,i,wfd,fret,rfd1,count,wfd2;
	char s[4],t[4],u[4],v[4];
	char *argv[2];
	Request d,e;
	printf("Pid :%d server is begin\n",getpid());
	init=initialisation;
	(*init)();
	i=0;
	while(1)
	{
		msgrcv(11,&d,sizeof(Request),0,0);
		printf("count---->%d\n",count);
		printf("rfd---->%d\n",rfd);
		printf("pid---->%d\n",d.pid);
		printf("opr---->%c\n",d.opr);
		
		printf("opr in loop----%c\n",d.opr);
		switch(d.opr)
		{
			case '+':
				printf("opr in case----%c\n",d.opr);
				fret=fork();
				switch(fret)
				{
					case 0:
						printf("waiting for Read for pc1\n");
						argv[0]="pc1";
						argv[1]=NULL;
						execv("./pc1",argv); 
					default: 
						msgsnd(12,&d,sizeof(Request),0);
				}
				break;
			case '-':
				printf("opr in case----%c\n",d.opr);
				fret=fork();
				switch(fret)
				{
					case 0:
						printf("waiting for Read for pc2\n");
						argv[0]="pc2";
						argv[1]=NULL;
						execv("./pc2",argv); 
					default: 
						msgsnd(12,&d,sizeof(Request),0);
				}
				break;
			case '*':
				printf("opr in case----%c\n",d.opr);
				fret=fork();
				switch(fret)
				{
					case 0:
						argv[0]="pc3";
						argv[1]=NULL;
						execv("./pc3",argv); 
					default: 
						msgsnd(12,&d,sizeof(Request),0);
				}
				break;
			default:
				printf("sorry ur program is not properly working\n");
		}
		msgrcv(13,&d,sizeof(Request),0,0);
		printf("rfd1---->%d\n",rfd1);
		printf("pid---->%d\n",e.pid);
		printf("result in server---->%d\n",e.result);
		
	//	kill(e.pid,SIGALRM);
		sem();
		set_val();
		sem_p();
		msgsnd(14,&d,sizeof(Request),0);
		printf("rfd1---->%d\n",rfd1);
		printf("count---->%d\n",count);
		printf("pid wfd2---->%d\n",e.pid);
		printf("result---->%d\n",e.result);
		close(wfd2);
		printf("i------------------------------------------->%d\n\n",i);
		i++;
	}
		sem_v();
	unlink("fifo1");
	unlink("fifo2");
	unlink("fifo3");
	unlink("fifo4");
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
