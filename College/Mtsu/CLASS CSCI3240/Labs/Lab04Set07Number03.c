/* Name: 	Timothy Beckett
 * Lab:		4
 * Set:		7
 * Number:	3
 * Description: Write a program that takes username and password from the user. Your program should
 * compare the input to the pre-stored username and password in the “userdata.txt” file.
 * Sample Content of userdata.txt:
 * user1 password1 75000.00
 * user2 password2 45950.75
 * user3 password3 65230.75
 * user4 password4 55550.75
 * user5 password5 95255.75
 * If the username and password match with any row in the userdata.txt file, display the
 * numerical data associated with that row.
 * Else, print the “username/password mismatch!!!” message.
 * A typical interaction with the program may look like this:
 * Usename: user3
 * Password: password3
 * The amount is: 65230.75
 * In case of wrong username or password:
 * Username: user1
 * Password: wrongPassword
 * username/password mismatch!!!
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define ARRAY_SIZE 128

struct UserData
{
    char Username[ARRAY_SIZE];
    char Password[ARRAY_SIZE];
    double Amount;
};

int ReadDatabase(char *filename, struct UserData *database, int *size);
void GetUsernameAndPassword(char *username, char *password);
int Find(struct UserData *database, int size, char *username, char *password, int *i);

int main(int argc, char** argv)
{   
    // check for filename.
    if (2 < argc)
    {
        printf("Filename not found\n");
        return 1;
    }
    
    char *filename =  *(argv+1), username[ARRAY_SIZE], password[ARRAY_SIZE];
    struct UserData database[ARRAY_SIZE];
    int size, i;

    // if fail get out
    if (ReadDatabase(filename, database, &size))
        return 1;
    
    GetUsernameAndPassword(username, password);

    // if fail get out
    if (Find(database, size, username, password, &i))
        return 1;
    
    printf("The amount is: %lf\n", database[i].Amount);
    
    return 0;
}

// Builds the user database.
// returns 0 for success.
// returns 1 for fail.
int ReadDatabase(char *filename, struct UserData *database, int *size)
{
    FILE *fptr;
    char username[ARRAY_SIZE], password[ARRAY_SIZE];
    double amount;
    int i; // database index;
    
    // opening the file pointer to read mode.
    if ((fptr = fopen(filename, "r")) == NULL)    
    {
        printf("Error opening file\n");
        
        return 1;
    }
    
    // setup input variables
    bzero(username, ARRAY_SIZE);
    bzero(password, ARRAY_SIZE);
    amount = 0;
    i = 0;
    
    // read from the file until you get to eof
    // print every 10 characters to a new line
    while(fscanf(fptr, "%128s %128s %lf", username, password, &amount) != EOF && i < ARRAY_SIZE)
    {
        // add values into the database.
        strncpy((database + i)->Username, username, strlen(username));
        strncpy((database + i)->Password, password, strlen(password));
        (database + i)->Amount = amount;        
        
        // reset input variables
        bzero(username, ARRAY_SIZE);
        bzero(password, ARRAY_SIZE);
        amount = 0;
        i++;
    }

    // return the number of records in the database
    *size = i;
    
    // closing the file pointer
    fclose(fptr);
    
    return 0;
}

// Collect the username and password and return it in the respective char array pointers.
void GetUsernameAndPassword(char *username, char *password)
{
    printf("Enter the Username:");
    scanf("%128s", username);
    printf("Enter the Password:");
    scanf("%128s", password);        
}

// Find the index of the correct database record and sets the value to the supplied index pointer
// returns 0 for success
// returns 1 for fail
int Find(struct UserData *database, int size, char *username, char *password, int *i)
{
    for ((*i) = 0; (*i) < size; (*i)++)
        if(0 == strcmp((database + *i)->Username, username) && 0 == strcmp((database + *i)->Password, password))
            return 0;
    
    printf("username/password mismatch!!!\n");
    
    return 1;
}
