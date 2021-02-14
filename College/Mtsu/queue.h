# include <stdio.h>
# ifndef BOOLEAN
# define BOOLEAN
# define TRUE 1
# define FALSE 0
# endif
# ifndef CHAR_QUEUE
# define CHAR_QUEUE

struct QueueTrack
{
	int front,
	    back,
	    size;
};

void initQueue(char the_queue[], struct QueueTrack* fb, int size)
{
	int i;

	(*fb).front = 0;
	(*fb).back = 0;

	(*fb).size = size;

	for(i = 0; i < (*fb).size; i++)
		the_queue[i] = (char)0;
}

int enqueue(char the_queue[], struct QueueTrack* fb, char data)
{
	if(((*fb).front + 1) % (*fb).size == (*fb).back)
		return FALSE;
	
	the_queue[(*fb).front] = data;

	(*fb).front = ((*fb).front + 1) % (*fb).size;

	return TRUE;
}

char dequeue(char the_queue[], struct QueueTrack* fb)
{
	char temp;
	
	if((*fb).front == (*fb).back)
		return (char)0;

	temp = the_queue[(*fb).back];

	(*fb).back = ((*fb).back + 1) % (*fb).size;

	return temp;	
}

# endif
