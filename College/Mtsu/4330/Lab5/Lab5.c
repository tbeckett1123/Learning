/* Programmer:		Tim (The Enchanter) Beckett
 * Class:		CSCI 4330
 * Instructor:		Dr. Pettey
 * Date Due:		04-11-07
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
# include "/usr/local/home/accts/pettey/mpich2-1.0.5p3/mpich2i/include/mpi.h"
# include <stdlib.h>
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


void HugeTrackOfLand(int rank, int nProcs, MPI_Status status);
void printWorld();
int readPlayerData();
void initWorld();
void TheBridgeOfDeath();
void BringOutYourDead(int hugeTrackOfLand);
void ImFeelingBetterIFeelHappy();
void dequeuePlayers();
void dragonYumYum(int hugeTrackOfLand);
void decomposeDragon();
void decomposeHTOL(int HTOL);
void recomposeDragon();
void recomposeHTOL(int HTOL);


struct QueueTrack fbs, htolp[MAX_THREAD];
struct player_t player_queue[MAX_PLAYERS * 6 + 1], hugeTracksOfLand_population[MAX_THREAD][MAX_PLAYERS + 1];

int playerNumber[MAX_PLAYERS+1];
int playerStatus[MAX_PLAYERS+1];
char playerType[MAX_PLAYERS+1];
int queueData[4];

int EBdecomp[3];


struct rItr evilBunny; /* The evil bunny is the dragon */ 

int main(int argc, char** argv)
{
	int rank, nProcs, index, finished, i;
	MPI_Status status;
	
	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &nProcs);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if(rank == 0)
	{

		initWorld();
	
		finished = FALSE;
		
		if(readPlayerData() == TRUE)
		{
			dequeuePlayers();
	
			printWorld();
		
			for(index = 0; index < MAX_EPOCH; index++)
			{

				for(i = 1; i < nProcs; i++)
					MPI_Send(&finished, 1, MPI_INT, i, 5, MPI_COMM_WORLD);
				
				decomposeDragon();
				
				for(i = 1; i < nProcs; i++)
				{
					MPI_Send(&EBdecomp, 3, MPI_INT, i, 6, MPI_COMM_WORLD);

					decomposeHTOL(i-1);

					MPI_Send(&playerNumber, MAX_PLAYERS + 1, MPI_INT, i, 1, MPI_COMM_WORLD);
					MPI_Send(&playerType, MAX_PLAYERS + 1, MPI_CHAR, i, 2, MPI_COMM_WORLD);
					MPI_Send(&playerStatus, MAX_PLAYERS + 1, MPI_INT, i, 3, MPI_COMM_WORLD);
					MPI_Send(&queueData, 4, MPI_INT, i, 4, MPI_COMM_WORLD);
				}

				
				//receive data here
					//receive htolp data after battle

				for(i = 1; i < nProcs; i++)
				{
					MPI_Recv(&playerNumber, MAX_PLAYERS + 1, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
					MPI_Recv(&playerType, MAX_PLAYERS + 1, MPI_CHAR, i, 2, MPI_COMM_WORLD, &status);
					MPI_Recv(&playerStatus, MAX_PLAYERS + 1, MPI_INT, i, 3, MPI_COMM_WORLD, &status);
					MPI_Recv(&queueData, 4, MPI_INT, i, 4, MPI_COMM_WORLD, &status);
		
					//update local data
					recomposeHTOL(i-1);
				}
				
				ImFeelingBetterIFeelHappy();
			
				TheBridgeOfDeath();

				dequeuePlayers();

				printWorld();
			}
		}
		
		finished = TRUE;

		for(index = 1; index < nProcs; index++)
			MPI_Send(&finished, 1, MPI_INT, index, 5, MPI_COMM_WORLD);
	}
	else
	{
		HugeTrackOfLand(rank, nProcs, status);
	}
	
	MPI_Finalize();
	
	return 0;
}

void decomposeDragon()
{
	EBdecomp[0] = evilBunny.mod;
	EBdecomp[1] = evilBunny.sum;
	EBdecomp[2] = evilBunny.value;
}

void decomposeHTOL(int rank)
{
	struct player_t temp;
	int i;
	
	queueData[0] = htolp[rank].back;
	queueData[1] = htolp[rank].front;
	queueData[2] = htolp[rank].size;
	queueData[3] = htolp[rank].realSize;
	
	for(i = 0; i < MAX_PLAYERS + 1; i++)
	{
		temp = hugeTracksOfLand_population[rank][i];
		
		playerNumber[i] = temp.number;
		
		playerStatus[i] = temp.status;
	
		playerType[i] = temp.type;

//		printf("decomp rank %d i %d number %d status %d type %c\n", rank, i, playerNumber[i], playerStatus[i], playerType[i]);
	}
	
}

void recomposeHTOL(int rank)
{
	struct player_t temp;
	int i;

	htolp[rank].back = queueData[0];
	htolp[rank].front = queueData[1];
	htolp[rank].size = queueData[2];
	htolp[rank].realSize = queueData[3];

	for(i = 0; i < MAX_PLAYERS + 1; i++)
	{
		initPlayer(&temp, playerStatus[i], playerNumber[i], playerType[i]);

		
//		printf("recomp rank %d i %d number %d status %d type %c\n", rank, i, playerNumber[i], playerStatus[i], playerType[i]);
		hugeTracksOfLand_population[rank][i] = temp;
	}
}

void recomposeDragon()
{
	evilBunny.mod = EBdecomp[0];
	evilBunny.sum = EBdecomp[1];
	evilBunny.value = EBdecomp[2];
}

void HugeTrackOfLand(int rank, int nProcs, MPI_Status status)
{        	
	int i, a, b, h, hugeTrackOfLand, fin;
	struct player_t temp;
	char check;

	initWorld();
	
	MPI_Recv(&fin, 1, MPI_INT, 0, 5, MPI_COMM_WORLD, &status);
	
	while(fin == FALSE)
	{

		MPI_Recv(&EBdecomp, 3, MPI_INT, 0, 6, MPI_COMM_WORLD, &status);
		
		recomposeDragon();
		
		//receive htolp data here
		
		MPI_Recv(&playerNumber, MAX_PLAYERS + 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&playerType, MAX_PLAYERS + 1, MPI_CHAR, 0, 2, MPI_COMM_WORLD, &status);
		MPI_Recv(&playerStatus, MAX_PLAYERS + 1, MPI_INT, 0, 3, MPI_COMM_WORLD, &status);
		MPI_Recv(&queueData, 4, MPI_INT, 0, 4, MPI_COMM_WORLD, &status);
		
		//update htolp data
		
		recomposeHTOL(rank - 1);

		h = a = 0;
		
		for(i = 0, b = htolp[rank-1].back; i < htolp[rank-1].realSize; i++, b = (b + 1) % htolp[rank-1].size)
			if(hugeTracksOfLand_population[rank-1][b].type == 'H')
				h++;
			else if(hugeTracksOfLand_population[rank-1][b].type == 'A')
				a++;

		if(h > a)
			check = 'A';
		else if(a > h)
			check = 'H';
		else
			check = '\0';
	
		if(check != '\0')
			for(i = 0, b = htolp[rank-1].back; i < htolp[rank-1].realSize; i++, b = (b + 1) % htolp[rank-1].size)
					if(check == hugeTracksOfLand_population[rank-1][b].type)
					{
						hugeTracksOfLand_population[rank-1][b].status = HONORED_DEATH_IN_BATTLE;
						i = MAX_PLAYERS + 1;
					}

		if(evilBunny.value == rank - 1) 
			dragonYumYum(rank - 1);

		BringOutYourDead(rank - 1);

		//send htolp data here

		decomposeHTOL(rank-1);

		MPI_Send(&playerNumber, MAX_PLAYERS + 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		MPI_Send(&playerType, MAX_PLAYERS + 1, MPI_CHAR, 0, 2, MPI_COMM_WORLD);
		MPI_Send(&playerStatus, MAX_PLAYERS + 1, MPI_INT, 0, 3, MPI_COMM_WORLD);
		MPI_Send(&queueData, 4, MPI_INT, 0, 4, MPI_COMM_WORLD);
				
		
		MPI_Recv(&fin, 1, MPI_INT, 0, 5, MPI_COMM_WORLD, &status);
	}
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
						       h+1);
		if(h == evilBunny.value)
			printf("%-10s%-10c%-10d\n", dragon, space, h+1);
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

