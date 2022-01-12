#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t mtx;
pthread_cond_t cond1,cond3,cond5;

int glob=1;

void *f1()
{
	for(;;)
	{
		pthread_mutex_lock(&mtx);
		if(glob!=1)
			pthread_cond_wait(&cond1,&mtx);
		printf("%d ",glob);
		glob=3;
		pthread_mutex_unlock(&mtx);
		pthread_cond_signal(&cond3);
	}
}
void *f3()
{
        for(;;)
        {
                pthread_mutex_lock(&mtx);
                if(glob!=3)
                        pthread_cond_wait(&cond3,&mtx);
                printf("%d ",glob);
                glob=5;
                pthread_mutex_unlock(&mtx);
                pthread_cond_signal(&cond5);
        }
}
void *f5()
{
        for(;;)
        {
                pthread_mutex_lock(&mtx);
                if(glob!=5)
                        pthread_cond_wait(&cond5,&mtx);
                printf("%d ",glob);
                glob=1;
                pthread_mutex_unlock(&mtx);
                pthread_cond_signal(&cond1);
        }
}


int main()
{
	pthread_t t1,t3,t5;
	pthread_cond_init(&cond1,NULL);
	pthread_cond_init(&cond3,NULL);
	pthread_cond_init(&cond5,NULL);
	pthread_mutex_init(&mtx,NULL);

	pthread_create(&t1,NULL,f1,NULL);
	pthread_create(&t3,NULL,f3,NULL);
	pthread_create(&t5,NULL,f5,NULL);

	pthread_join(t1,NULL);
	pthread_join(t3,NULL);
	pthread_join(t5,NULL);

	pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&cond1);
	pthread_cond_destroy(&cond3);
	pthread_cond_destroy(&cond5);
}
















