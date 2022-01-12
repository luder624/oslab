#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int glob=0;
pthread_mutex_t mtx;
void *add(void *arg)
{
	int i;
	int count=*((int*)arg);
	for(i=0;i<count;i++)
	{
		pthread_mutex_lock(&mtx);
		glob+=2;
		pthread_mutex_unlock(&mtx);
	}
}
void *sub(void *arg)
{
	int i=0;
	int count=*((int*)arg);
	for(i=0;i<count;i++)
	{
		pthread_mutex_lock(&mtx);
		glob-=2;
		pthread_mutex_unlock(&mtx);
	}
}


int main(int argc,char*argv[])
{
	pthread_t t1,t2,t3;
	int count=atoi(argv[1]);
	pthread_mutex_init(&mtx,NULL);
	pthread_create(&t1,NULL,add,&count);
	pthread_create(&t2,NULL,add,&count);
	pthread_create(&t3,NULL,sub,&count);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);

	printf("glob:%d\n",glob);
	pthread_mutex_destroy(&mtx);
	return 0;
}
