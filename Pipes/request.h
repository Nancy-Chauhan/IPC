typedef struct request
{
	int pid;
	int opr1;
	int opr2;
	char opt;
}Request;
void def(int sig)
{
	alarm_sig=1;
}
