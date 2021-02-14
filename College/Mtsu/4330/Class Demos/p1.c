# include <stdio.h>
# include <pthread.h>

pthread_mutex_t m1 =  PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 =  PTHREAD_MUTEX_INITIALIZER;

int sum1 = 0;
int sum2 = 0;

void* dead1 ( void* ignored)
{
	int mysum = 5;
	
	int i;
	
	for(i = 0; i<20; i++)
	{
		pthread_mutex_lock(&m1);
		if(sum1%5 == 0)
		{
			pthread_mutex_lock(&m2);
			sum1+=mysum;
			sum2+=sum1;
			printf("dead1 sum1 = %d sum2 = %d\n", sum1, sum2);
		}
		
		pthread_mutex_unlock(&m2);

	pthread_mutex_unlock(&m1);
	}
	pthread_exit(0);
}
void* dead2 ( void* ignored)
{
	int mysum = 3;
	
	int i;
	
	for(i = 0; i<20; i++)
	{
		pthread_mutex_lock(&m1);
		if(sum1%3 == 0)
		{
			pthread_mutex_lock(&m2);
			sum1+=mysum;
			sum2+=sum1;
			printf("dead2 sum1 = %d sum2 = %d\n", sum1, sum2);
		}
		
		pthread_mutex_unlock(&m2);

	pthread_mutex_unlock(&m1);
	}
	pthread_exit(0);
}

int main()
{
	pthread_t t1,t2;
	pthread_create(&t1,NULL,dead1, NULL);
	pthread_create(&t2,NULL,dead2, NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	return 0;
}
