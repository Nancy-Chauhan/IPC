typedef struct request
{
	char opr;
	int oper1;
	int oper2;
	int result;
	int written;
	long pid;
	long type;
}Request;
//extern sem_t a;
static int alarm_sig=0;
void def(int sig)
{
	alarm_sig=1;
	printf("def is called\n");
}
