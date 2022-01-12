#include<semaphore.h>
#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
sem_t *mutex;
int count=0;
void inc(void);
void dec(void);

int main(void)
{
	int i=0;
	mutex=sem_open("/mysem",O_CREAT,S_IRUSR|S_IWUSR,1);
	pthread_t id[4];
	pthread_create(&id[0],NULL,(void*)dec,NULL);
	pthread_create(&id[1],NULL,(void*)inc,NULL);
	pthread_create(&id[2],NULL,(void*)dec,NULL);
	pthread_create(&id[3],NULL,(void*)inc,NULL);
	for(i=0;i<4;i++)
		pthread_join(id[i],NULL);
	printf("\noutput is %d\n",count);
	pthread_exit(NULL);
}
void inc(void)
{
	int i=0;
	for(i=0;i<2500000;i++)
	{
		sem_wait(mutex);
		count++;
		sem_post(mutex);
	}
	pthread_exit(NULL);
}
void dec(void)
{
        int i=0;
        for(i=0;i<2500000;i++)
        {
                sem_wait(mutex);
                count--;
                sem_post(mutex);
        }

        pthread_exit(NULL);
}


