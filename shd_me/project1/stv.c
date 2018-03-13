#include"header.h"
#include"decleration.h"
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};
int key;
int sem()
{
	key=semget(123,1,0666|IPC_CREAT);
	printf("key value of semget=%d\n",key);
}
int set_val()
{
	int c;
	union semun a;
	a.val=1;
	c=semctl(key,0,SETVAL,a);
	printf("key value of set semctl=%d\n",c);
}	
int del_val()
{
	int c;
	union semun a;
	a.val=1;
	c=semctl(key,0,IPC_RMID,a);
	printf("key value of del semctl=%d\n",c);
}	
int sem_v()
{
	int c;
	struct sembuf b;
	b.sem_num=0;
	b.sem_op=1;
	b.sem_flg=SEM_UNDO;
	c=semop(key,&b,1);
	printf("key value of semop=%d\n",c);
}	
int sem_p()
{
	int c;
	struct sembuf b;
	b.sem_num=0;
	b.sem_op=-1;
	b.sem_flg=SEM_UNDO;
	c=semop(key,&b,1);
	printf("key value of ssemop=%d\n",c);
}	

