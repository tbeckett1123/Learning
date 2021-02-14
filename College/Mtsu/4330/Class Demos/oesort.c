#include <stdio.h>
#include <pthread.h>

int list[16];
int count;
int thread_done = 0;

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c1 = PTHREAD_COND_INITIALIZER;

void * sort( void * args)
{
     int me = *((int *) args);
     int index = 2*me + 1;
     int temp;
     int i;

     for(i=0;i<count/2;i++){
	if (list[index-1] > list [index])
	{
		temp = list[index-1];
		list[index-1] = list[index];
		list[index] = temp;
	}

	pthread_mutex_lock(&m1);
	thread_done++;
	if(thread_done < count/2)
		pthread_cond_wait(&c1,&m1);
	else
	{
		thread_done = 0;
		pthread_cond_broadcast(&c1);
	}
	pthread_mutex_unlock(&m1);

	if ((index < count-1)&&(list[index] > list [index+1]))
	{
		temp = list[index+1];
		list[index+1] = list[index];
		list[index] = temp;
	}
	pthread_mutex_lock(&m1);
	thread_done++;
	if(thread_done < count/2)
		pthread_cond_wait(&c1,&m1);
	else
	{
		thread_done = 0;
		pthread_cond_broadcast(&c1);
	}
	pthread_mutex_unlock(&m1);
     }
     pthread_exit(0);
}

int main()
{
	int i;
	pthread_t ids[8];
	int args[8];

	printf("input number in list\n");
	scanf("%d",&count);
	printf("input list\n");
	for (i=0;i<count;i++)
		scanf("%d",&list[i]);
	for (i=0;i<count/2;i++)
	{
		args[i] = i;
		pthread_create(&ids[i],NULL,sort,(void *) &args[i]);
	}
	for (i=0;i<count/2;i++)
		pthread_join(ids[i],NULL);

	for (i=0;i<count;i++)
		printf("%d ",list[i]);
	return 0;
}


