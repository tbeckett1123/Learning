/* Name: 	Timothy Beckett
 * Lab:		5
 * Set:		8
 * Number:	2
 * Description: Create a structure in C to store a batsman’s name, runs scored, the number of
 * dismissals, and the batting average. In the program, read the data (name, runs, and
 * no. of dismissals) of five players and display the batting average of the player whose
 * name is entered by the user. The batting average is given by the total runs/total no. of
 * dismissals.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# define LENGTH 128
# define BUFFER_SIZE 15
# define MAX 5

struct Batsman
{
    char Name[LENGTH];
    unsigned int Runs;
    unsigned int Dismissals;
};

char *place[4] = { "th", "st", "nd", "rd" };

void GetBatters(struct Batsman *batters);
void PrintBatters(struct Batsman *batters);
char* FormattedName(char *name);

int main(int argc, char** argv)
{   
    struct Batsman batters[MAX];    
   
    GetBatters(batters);    
    PrintBatters(batters);
    
    return 0;
}

void GetBatters(struct Batsman *batters)
{   
    for (int i = 0; i < MAX; i++)
    {
        // pi is for printing 1st, 2nd, 3rd, 4th, 5th
        int pi = i + 1;
        int j = pi > 3 ? 0 : pi;

        bzero((batters + i)->Name, LENGTH);

        printf("Enter the %d%s batter's name:\n", pi, place[j]);
        fgets((batters + i)->Name, LENGTH, stdin);
        (batters + i)->Name[strcspn((batters + i)->Name, "\n")] = '\0';  // Remove trailing newline

        printf("Enter the %d%s batter's runs:\n", pi, place[j]);        
        // * I was experiencing a weird error with a new line gettting stuck in the stdin buffer
        // * after the first execution of the GetBatter function. I went through several interations
        // * of the function to find 1 that works w/o error.
        // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
        char runsInput[10];
        fgets(runsInput, sizeof(runsInput), stdin);
        sscanf(runsInput, "%u", &(batters + i)->Runs);

        printf("Enter the %d%s batter's dismissals:\n", pi, place[j]);
        char dismissalsInput[10];
        fgets(dismissalsInput, sizeof(dismissalsInput), stdin);
        sscanf(dismissalsInput, "%u", &(batters + i)->Dismissals);
    }    
}


void PrintBatters(struct Batsman *batters)
{
    int i = 0;         
    
    // printing the database in a tabular format.
    
    // print header
    printf("Name%11s Runs  Dismissals Batting Average\n", " "); // printing a table heading.
    for (int i = 0; i < MAX; i++)
    {        
        // print formatted record to fit column lengths
        printf("%-15s %-5u %-10u %-5.9f\n", FormattedName((batters + i)->Name), (batters + i)->Runs, (batters + i)->Dismissals, (batters + i)->Runs / (double)((batters + i)->Dismissals > 0 ? (double)(batters + i)->Dismissals : 1.0));
    }
}

// printing a substring of the name for tabular data.
char buffer[BUFFER_SIZE]; // I needed a buffer that would allow me to return a substring
char* FormattedName(char *name)
{
    int sLength = strlen(name);
    
    // if the name is less within the column length return.
    if (sLength <= BUFFER_SIZE) 
        return name;
    
    // setup formatted name
    //clear the buffer
    bzero(buffer, BUFFER_SIZE);    
    
    // the 3 dots indicates the name has been trucated for column
    strncpy(buffer, name, BUFFER_SIZE - 4);
    strcat(buffer, "...");
    
    return buffer;
}