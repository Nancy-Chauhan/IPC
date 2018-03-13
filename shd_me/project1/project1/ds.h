typedef struct request
{
	long pid;
	int opt[3];
	char opr;
	int result;
}Request;
static int alarm_sig=0;
void def(int sig)
{
	alarm_sig=1;
	printf("def is called\n");
}
