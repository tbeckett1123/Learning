/* Lab:  Simpson's and Trapezoidal Rule
   Author:  Dr. Pettey
   Date:  February 25, 2003
   Purpose:  To calculate the area under the curve
              3*(sin(x/2)^3)
             from 0 to PI
             Using simpson's rule and the trapezoidal
	     rule and compare the results.
             There are no more than 10 partitions.
*/     

/*need the thread library for threads and the math
  library for the sin function */
#include <stdio.h>
#include <pthread.h>
#include <math.h>

#define PI 3.14159

float width;                /* the width of a segment*/
float tsum = 0.0;           /* the trapezoidal result*/
float ssum = 0.0;           /* simpson's result*/
pthread_mutex_t mutex1;     /* mutual exclusion variable for simpsons*/
pthread_mutex_t mutex2;     /* mutual exclusion variable for trapezoidal*/

/*Calculate one segment of the area using simpson's rule*/
void *simpsons(void *mine)
{
	float partial_sum = 0.0;      /*area under my segment*/
	int me = *((int *)mine);      /*which segment is mine */
	double x1,y1,z,x2,y2,x3,y3;   /*temp variables for calculations*/
	
	z = width;
	x1 = me*z;                    /*my left endpoint*/
	x2 = me*z + z/2.0;            /*my midpoint*/
	x3 = me*z + z;                /*my right endpoint*/
	
	/*calculate the height of the curve at each x value*/
	y1 = sqrt(3*sin(x1/2.0)*sin(x1/2.0)*sin(x1/2.0));
	y2 = sqrt(3*sin(x2/2.0)*sin(x2/2.0)*sin(x2/2.0));
	y3 = sqrt(3*sin(x3/2.0)*sin(x3/2.0)*sin(x3/2.0));
	
	/*calculate the area in my segment*/
	partial_sum = (y1 + 4*y2 + y3)*z/6.0;	
		
        /*increment the global area*/
	pthread_mutex_lock(&mutex1);
		ssum += partial_sum;
	pthread_mutex_unlock(&mutex1);

}

/*Calculate one segment of the area using trapezoidal rule*/
void *trapezoid(void *mine)
{
	float partial_sum = 0.0;       /*area for my segment*/
	int me = *((int *)mine);       /*which area is mine*/
	double x1,y1,z,x2,y2;          /*temp calculation variables*/
	
	z = width;

	/*calculate left and right endpoint*/
	x1 = me*z;
	x2 = me*z + z;

	/*calculate the height of the curve at each x*/
	y1 = sqrt(3*sin(x1/2.0)*sin(x1/2.0)*sin(x1/2.0));
	y2 = sqrt(3*sin(x2/2.0)*sin(x2/2.0)*sin(x2/2.0));

	/*calculate my area*/
	partial_sum = (y1 + y2)*z/2.0;	
		
	/*increment the global sum*/
	pthread_mutex_lock(&mutex2);
		tsum += partial_sum;
	pthread_mutex_unlock(&mutex2);

}

/************************begin main***********************/
main()
{
	int no_processes;                    /*number of threads/segments*/
	int i;                               /*loop variable*/
	int is[10];                          /*array for designating segment numbers*/
	pthread_t threadt[10];               /*thread id array for trapezoid*/
	pthread_t threads[10];               /*thread id array for simpson*/

	/*initialize mutual exclusion variables*/
	pthread_mutex_init(&mutex1,NULL);
	pthread_mutex_init(&mutex2,NULL);

	/*determine the number of partitions...which is the number of threads*/
	printf("input the number of partitions\n");
	scanf("%d",&no_processes);

	/*the width is the same for each segment so make it global*/
	width = PI/no_processes;

	/*create trapezoid threads*/
	for(i=0;i<no_processes;i++)
	{
		is[i]=i;
		if(pthread_create(&threadt[i],NULL,trapezoid,(void *)&is[i]) != 0)
			perror("Pthread_create fails");
	}

	/*create simpson threads*/
	for(i=0;i<no_processes;i++)
	{
		if(pthread_create(&threads[i],NULL,simpsons,(void *)&is[i]) != 0)
			perror("Pthread_create fails");
	}

	/*wait for all trapezoid threads*/
	for(i=0;i<no_processes; i++)
		if (pthread_join(threadt[i],NULL) != 0)
			perror("Trapezoid Pthread_join fails");

	/*wait for all simpson threads*/
	for(i=0;i<no_processes; i++)
		if (pthread_join(threads[i],NULL) != 0)
			perror(" Simpson Pthread_join fails");

	/*print the area for each*/
	printf("The area under the curve using trapezoidal is %f\n",tsum);
	printf("The area under the curve using simpsons is %f\n",ssum);
}
