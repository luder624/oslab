#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<wait.h>

int main()
{
	int f=fork();
	if(f==0)
	{
		printf("child pid:%d\n",getpid());
		//kill(getppid(),SIGTERM);
		for(;;);
	}
	else
	{
		printf("parent pid:%d\n",getpid());
		wait(NULL);
	}

}
