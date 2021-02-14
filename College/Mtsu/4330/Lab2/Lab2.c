/* Programmer:		Tim (The Enchanter) Beckett
 * Class:		CSCI 4330
 * Instructor:		Dr. Pettey
 * Date Due:		02-21-07
 * Destriction:		This program simulates a game
 * 			server.  The game takes place
 * 			on 4 continents.  Each cont-
 * 			inent can have up to 5 players
 * 			There are 2 teams that battle
 * 			on the continents; the team
 * 			with the most players on a
 * 			paticular continent wins the
 * 			battle for that epoch on that
 * 			continent. After the battle
 * 			for the continent if the 
 * 			dragon is on the continent,
 * 			it gets to feed.  It likes
 * 			the taste of the A-Team, for
 * 			they are tender and juicey.
 * 			However, if there aren't any
 * 			of the A-Team on the cont-
 * 			inent, it will eat players
 * 			from the H-Team.  After a
 * 			player is killed, he is put
 * 			back into the waiting queue,
 * 			and will be reborn on the 
 * 			next epoch when it is his 
 * 			turn.
 * Inputs:		The inputs are from a file.
 * 			The program expects there to
 * 			be a string of A's and 'H's.
 * 			There is a special case however;
 * 			The placement of the dragon, it
 * 			will be signified by a D followed
 * 			by a number from 0 to 3 which
 * 			will tell which continent the
 * 			dragon starts on.
 * 			<----- Important --------->
 * 			THERE CAN BE NO SPACES OR NULL
 * 			CHARS IN THE STRING.  IT IS
 * 			EXPECTED THAT THE STRING WILL
 * 			BE A SET OF CHARATORS.
 ***************************************************/

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# define MAX_THREAD 4
# define MAX_PLAYERS 5
# define MAX_EPOCH 10 
# define TENDER_MORSELS MAX_PLAYERS
# define HAVE_EATEN_MORSELS TENDER_MORSELS * MAX_THREAD + 1
# define FULL 1
# define NOT_FULL 0
# define ALIVE 1
# define BIRTH ALIVE
# define REENCARNATE ALIVE
# define WAITING -1
# define DEAD 0
# define HONORED_DEATH_IN_BATTLE DEAD
# define DEATH_BY_DRAGON DEAD
# define TRUE 1
# define FALSE 0

struct rItr /*reverse itorator data type*/
{
	int mod, value, sum;
};

void rItrInit(struct rItr* temp, unsigned int value);
int rItrAssign(struct rItr* temp, unsigned int value);
void rItrPP(struct rItr* temp);

/*End of Reverse itorator data type*/

/*Queue Data Type*/

struct player_t
{
	int	status,
		number;
	char	type;
};
void initPlayer(struct player_t* player, int status, int number, char type);

struct QueueTrack
{
	int front,
	    back,
	    size,
	    realSize;
};

void initQueue(struct player_t the_queue[], struct QueueTrack* fb, int size);
int enqueue(struct player_t the_queue[], struct QueueTrack* fb, struct player_t data);
struct player_t dequeue(struct player_t the_queue[], struct QueueTrack* fb);
int renqueue(struct player_t the_queue[], struct QueueTrack* fb, struct player_t data);

/*End of Queue Data Type*/


void * HugeTrackOfLandThread(void * thread_id_ptr);
void printWorld();
int readPlayerData();
void initWorld();
void TheBridgeOfDeath();
void BringOutYourDead(int hugeTrackOfLand);
void ImFeelingBetterIFeelHappy();
void dequeuePlayers();
void dragonYumYum(int hugeTrackOfLand);



pthread_mutex_t lock[MAX_THREAD]; 
void lockAll();
void unlockAll();

struct QueueTrack fbs, htolp[MAX_THREAD];
struct player_t player_queue[MAX_PLAYERS * 6 + 1], hugeTracksOfLand_population[MAX_THREAD][MAX_PLAYERS + 1];

struct rItr evilBunny; /* The evil bunny is the dragon */ 

int finished[MAX_THREAD];


int main()
{
	pthread_t id[MAX_THREAD];	   /*player thread id*/
	int	  index_arr[MAX_THREAD],   /*player thread id index*/
		  index;		   /*index*/

	initWorld();
	
	
	if(readPlayerData() == FALSE) return -1;

	lockAll();
	
	dequeuePlayers();

	printWorld();

	unlockAll();

	for(index = 0; index < MAX_THREAD; index++)
	{
		/*spawn new thread*/
		index_arr[index] = index; /*set the element of the array of players, for the player in question,
					  to the process id that is assigned to handle his/her thread*/

		pthread_create(&id[index], NULL, HugeTrackOfLandThread, (void *)&index_arr[index]);
	}

	for(index = 0; index < MAX_EPOCH; index++)
	{
		lockAll();
		
		ImFeelingBetterIFeelHappy();
		
		TheBridgeOfDeath();

		dequeuePlayers();

		printWorld();

		unlockAll();
	}
	
	/*finializing: terminating all processes for program shutdown*/
	
	for(index = 0; index < MAX_THREAD; index++)
		finished[index] = TRUE;

	for(index = 0; index < MAX_THREAD; index++)
		pthread_join(id[index], NULL);	
	
	return 0;
}

void * HugeTrackOfLandThread(void * thread_id_ptr)
{
	int thread_id = *((int*)thread_id_ptr), /*get the id from the ptr*/
	    i, h, a, b;
	char check;

	while(finished[thread_id] == FALSE)
	{
		pthread_mutex_lock(&lock[thread_id]);
		
		a = 0;
		h = 0;
		
		for(i = 0, b = htolp[thread_id].back; i < htolp[thread_id].realSize; i++, b = (b + 1) % htolp[thread_id].size)
			if(hugeTracksOfLand_population[thread_id][b].type == 'H')
				h++;
			else if(hugeTracksOfLand_population[thread_id][b].type == 'A')
				a++;

		if(h > a)
			check = 'A';
		else if(a > h)
			check = 'H';
		else
			check = '\0';
	
		if(check != '\0')
		for(i = 0, b = htolp[thread_id].back; i < htolp[thread_id].realSize; i++, b = (b + 1) % htolp[thread_id].size)
				if(check == hugeTracksOfLand_population[thread_id][b].type)
				{
					hugeTracksOfLand_population[thread_id][b].status = HONORED_DEATH_IN_BATTLE;
					i = MAX_PLAYERS + 1;
				}

		if(evilBunny.value == thread_id) 
			dragonYumYum(thread_id);

		BringOutYourDead(thread_id);

		pthread_mutex_unlock(&lock[thread_id]);
	}
	
	pthread_exit(0);
}

/* displays the world */
void printWorld()
{
	int h, i, j;
	char *player = "Player", *team = "Team", *continent = "Continent", *queue = "queue", *dragon = "Dragon", space = ' ';

	printf("\n\n\n<~~~~~~~~~~~~~~~~~~ STARTING NEW EPOCH ~~~~~~~~~~~~~~~~~~>\n\n\n");
	
	printf("%-10s%-10s%-10s\n", player, team, continent);

	for(h = 0; h < MAX_THREAD; h++)
	{
		for(i = 0, j = htolp[h].back; i < htolp[h].realSize; j = (j + 1) % htolp[h].size, i++)
			/*if(hugeTracksOfLand_population[h][j].status == ALIVE)*/
			   printf("%-10d%-10c%-10d\n", hugeTracksOfLand_population[h][j].number,
						       hugeTracksOfLand_population[h][j].type,
						       h);
		if(h == evilBunny.value)
			printf("%-10s%-10c%-10d\n", dragon, space, h);
	}

	for(i = fbs.back, j = 0; j < fbs.realSize; i = (i + 1) % fbs.size, j++)
			printf("%-10d%-10c%-10s\n", player_queue[i].number, player_queue[i].type, queue);
}

/* this function gets all player data and puts it in the player queue; it *
 * also  identifies the continent the dragon is supposed to be on.	  */
int readPlayerData()
{
	char data[35], dhtol[2] = {'\0','\0'};
	struct player_t temp;
	int size, i, r;
	FILE *fp;

	if(fp = fopen("players.dat", "r"))
	{		
		r = TRUE;
		fscanf(fp, "%s", &data);

		fclose(fp);
	
		size = strlen(data);

		if(size > 32)
		{
			printf("<**** ERROR IN INPUT ****>\ntruncating size to fit games specks\nif dragon is lost, the 4th continent is assume\n");
			size = 32;
		}

		for(i = 0; i < size; i++)
		{
			switch(data[i])
			{
			case 'A': 
			case 'H': initPlayer(&temp, BIRTH, i, data[i]);
				  enqueue(player_queue, &fbs, temp);
	 			  break;
			case 'D': i++;
				  dhtol[0] = data[i];			  
				  rItrAssign(&evilBunny, atoi(dhtol));
	 			  break;
			default:
				printf("<**** ERROR IN INPUT ****>\nskipping data item\n");
			};
		}
	}
	else
	{	
		r = FALSE;
		printf("<**** ERROR *****>\nthe file players.dat failed to open\n");
	}

	return r;
}

/* this function initializes all the variables needed for the game to function */
void initWorld()
{	
	int i,j;

	/*set up finished flags*/
	for(i = 0; i < MAX_THREAD; i++)
	{
		finished[i] = FALSE;
		pthread_mutex_init(&lock[i], NULL);
	}

	/*prepare the evil bunny (the dragon)*/

	rItrInit(&evilBunny, MAX_THREAD);

	/*set up the player waiting queue*/
	initQueue(player_queue, &fbs, MAX_PLAYERS * 6 + 1);

	/*set up each huge track of land (continent)*/
	for(i = 0; i < MAX_THREAD; i++)
		initQueue(hugeTracksOfLand_population[i], &htolp[i], MAX_PLAYERS + 1);
}

/* "Who would cross the Bridge of Death must answer me these questions 
 * three, ere the other side he see. 
 * What is your name?
 * What is your quest?
 * What... is the air-speed velocity of an unladen swallow?" 
 * -- bridge keeper from MP's Quest for the Holy Grail
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void TheBridgeOfDeath()
{
	struct player_t ptemp[MAX_THREAD][2];
	int i; 

	rItrPP(&evilBunny); /* the bunny hops to the next continent */

	for(i = 0; i < MAX_THREAD; i++)
	{
		ptemp[i][0] = dequeue(hugeTracksOfLand_population[i], &htolp[i]);
		ptemp[i][1] = dequeue(hugeTracksOfLand_population[i], &htolp[i]);
	}

	for(i = 0; i < MAX_THREAD; i++)
	{
		enqueue(hugeTracksOfLand_population[(i + 1) % MAX_THREAD], &htolp[(i + 1) % MAX_THREAD], ptemp[i][0]);
		enqueue(hugeTracksOfLand_population[(i + 1) % MAX_THREAD], &htolp[(i + 1) % MAX_THREAD], ptemp[i][1]);
	}
}

/* This function cleans up all the dead bodies on the continents; 
 * don't try to give him live bodies it's against regulations. 
 ****************************************************************/
void BringOutYourDead(int hugeTrackOfLand)
{
	int h, i, j;
	struct player_t temp;

	for(h = 0; h < MAX_THREAD; h++)
		for(i = 0, j = htolp[h].back; i < htolp[h].realSize - 1; i++, j = (j + 1) % htolp[h].size)
			if(hugeTracksOfLand_population[h][j].status > hugeTracksOfLand_population[h][(j + 1) % htolp[h].size].status)
			{
				temp = hugeTracksOfLand_population[h][j];
				hugeTracksOfLand_population[h][j] = hugeTracksOfLand_population[h][(j + 1) % htolp[h].size];
				hugeTracksOfLand_population[h][(j + 1) % htolp[h].size] = temp;
			}
}

/* this function takes all dead players and puts them back into the player queue */
void ImFeelingBetterIFeelHappy()
{
	int i, hugeTrackOfLand;
	struct player_t temp;

	for(hugeTrackOfLand = 0; hugeTrackOfLand < MAX_THREAD; hugeTrackOfLand++)
			for(i = htolp[hugeTrackOfLand].back; i < htolp[hugeTrackOfLand].realSize; i = (i+1) % htolp[hugeTrackOfLand].size)
				 if(hugeTracksOfLand_population[hugeTrackOfLand][i].status == DEAD)
				 {
					temp = dequeue(hugeTracksOfLand_population[hugeTrackOfLand], &htolp[hugeTrackOfLand]);
					
					temp.status = REENCARNATE;

				 	enqueue(player_queue, &fbs, temp);
				 }
}

/* this function lets as many players as possiable onto each continent for the epoch */
void dequeuePlayers()
{
	int i;
	struct player_t temp;

	temp = dequeue(player_queue, &fbs);

	for(i = 0; i < MAX_THREAD; i++)
	{
		while(temp.type != '\0' && TRUE == enqueue(hugeTracksOfLand_population[i], &htolp[i], temp))
			temp = dequeue(player_queue, &fbs);		

		if(temp.type == '\0')
			i = MAX_THREAD + 1;
	}
		
	renqueue(player_queue, &fbs, temp);
}

/* "Do not meddle in the affairs of dragons 
 * for you are crunchy and taste good with 
 * ketchup." -- As quoted by Neal McClain
 ******************************************/
void dragonYumYum(int hugeTrackOfLand)
{
	int search;

	if(htolp[hugeTrackOfLand].realSize == 0)
		return;

	for(search = 0; search < TENDER_MORSELS; search++)
	{	
		if(hugeTracksOfLand_population[hugeTrackOfLand][search].status == ALIVE
		   && hugeTracksOfLand_population[hugeTrackOfLand][search].type == 'A')
		{
			hugeTracksOfLand_population[hugeTrackOfLand][search].status = DEATH_BY_DRAGON;
			search = HAVE_EATEN_MORSELS - 1;
		}
	}

	if(search != HAVE_EATEN_MORSELS)
		for(search = 0; search < TENDER_MORSELS; search++)
		{	
			if(hugeTracksOfLand_population[hugeTrackOfLand][search].status == ALIVE)
			{
				hugeTracksOfLand_population[hugeTrackOfLand][search].status = DEATH_BY_DRAGON;
				search = HAVE_EATEN_MORSELS;
			}
		}
}

void initQueue(struct player_t the_queue[], struct QueueTrack* fb, int size)
{
	int i;
	struct player_t temp;

	initPlayer(&temp, WAITING, WAITING, 'W');

	(*fb).front = 0;
	(*fb).back = 0;
	(*fb).realSize = 0;
	(*fb).size = size;

	for(i = 0; i < (*fb).size; i++)
		the_queue[i] = temp;
}

int enqueue(struct player_t the_queue[], struct QueueTrack* fb, struct player_t data)
{
	if(((*fb).front + 1) % (*fb).size == (*fb).back)
		return FALSE;
	
	the_queue[(*fb).front] = data;

	(*fb).front = ((*fb).front + 1) % (*fb).size;
	
	(*fb).realSize++;

	return TRUE;
}

int renqueue(struct player_t the_queue[], struct QueueTrack* fb, struct player_t data)
{
	struct rItr i;

	rItrInit(&i, (*fb).size);
	rItrAssign(&i, (*fb).back);
	rItrPP(&i);

	if(data.number != the_queue[i.value].number 
	   || data.type != the_queue[i.value].type 
	   || data.status != the_queue[i.value].status
	   || (*fb).realSize == 0)
		return FALSE;

	(*fb).back = i.value;
	(*fb).realSize++;

	return TRUE;
}

struct player_t dequeue(struct player_t the_queue[], struct QueueTrack* fb)
{
	struct player_t temp;

	initPlayer(&temp, 0, 0, '\0');

	if((*fb).front == (*fb).back)
		return temp;
	
	temp = the_queue[(*fb).back];

	(*fb).back = ((*fb).back + 1) % (*fb).size;
	
	(*fb).realSize--;

	return temp;	
}

void rItrInit(struct rItr* temp, unsigned int value)
{	
	(*temp).mod = value;
	(*temp).sum = 0;
	(*temp).value = value - 1;
}

int rItrAssign(struct rItr* temp, unsigned int value)
{
	if((*temp).mod - 1 < value)
		return FALSE;

	(*temp).value = value;
	(*temp).sum = (*temp).mod - 1 - value;

	return TRUE;
}

void rItrPP(struct rItr* temp)
{
	(*temp).sum = ((*temp).sum + 1) % (*temp).mod;
	(*temp).value = (*temp).mod - 1 - (*temp).sum;
}

void initPlayer(struct player_t* player, int status, int number, char type)
{
	(*player).status = status;
	(*player).number = number;
	(*player).type = type;
}

void lockAll()
{
	int i;

	for(i = 0; i < MAX_THREAD; i++)
		pthread_mutex_lock(&lock[i]);
}

void unlockAll()
{
	int i;

	for(i = 0; i < MAX_THREAD; i++)
		pthread_mutex_unlock(&lock[i]);
}

