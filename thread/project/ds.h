typedef struct request
{
	long pid;
	int oper1;
	int oper2;
	char opr;
	int result;
	int written;
	char text[2048];
}Request;
//extern sem_t a;
static int alarm_sig=0;
void def(int sig)
{
	alarm_sig=1;
	printf("def is called\n");
}
