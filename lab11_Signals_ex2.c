#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

struct sigaction newact;

void handler1(int sig_num)
{
	printf("How are you?\n");
}
void handler2(int sig_num)
{
	printf("I am fine!\n");
}
void alarmHandler()
{
	//printf("alarm is called\n");
	if(newact.sa_handler==handler1)
	{
		//printf("change\n");
		newact.sa_handler=handler2;
        	sigemptyset(&newact.sa_mask);
        	newact.sa_flags=0;
        	sigaction(SIGINT,&newact,NULL);
		alarm(3);
	}
	else if(newact.sa_handler==handler2)
	{
		newact.sa_handler=SIG_DFL;
		sigaction(SIGINT,&newact,NULL);
	}
	
}
int main()
{
	//signal(SIGINT, handler1);
	newact.sa_handler=handler1;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags=0;
	sigaction(SIGINT,&newact,NULL);
	signal(SIGALRM,alarmHandler);
	alarm(3);
	for(;;)
		pause();
}
