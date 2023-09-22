/* Name: 	Timothy Beckett
 * Lab:		5
 * Set:		8
 * Number:	3
 * Description: Create a structure “Student” to store the name of the student, student id, and score.
 * Your program should read the information of students from a file “student.csv” and
 * store them in an array of structures. Finally, your program should find and display
 * the name and student id of the student with the highest score.
 * 
 * Sample content of student.csv file:
 * Name, Student id, Score
 * John Doe, 12345678, 60
 * Bruce Wayne, 10000000, 79.3
 * Ada Lovelace, 12101815, 100
 * Charles Babbage, 12261791,99.9
 *
 * Hint: You may want to ignore the first line of the file (header).
 * - https://stdin.top/posts/csv-in-c/
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Student
{
    char* Name;
    char* Id;
    float Score;
    struct Student *Next;
};

// Structure way of tracking dynamic memory to free before ending program
struct Garbage
{
    void *Unit;
    struct Garbage *Next;
} *Head = NULL;

void AddToFinalizeList(void *unit);
void Finalize();
void Split(char splitter, char *text, char ***strings, int *indexCount);
int CharCount(char *string, char c, int length);
int LineCount(FILE *fptr);
char* Trim(char* str);
void LoadDatabase(char *filename, struct Student **students);
void FindHighScore(struct Student *students);

int main(int argc, char** argv)
{    
    char filename[] = "students.csv";
    struct Student *students = NULL;

    LoadDatabase(filename, &students);
    FindHighScore(students);    
    Finalize();

    return 0;
}

// Add Garbarge to clean
void AddToFinalizeList(void *unit)
{
    if (Head == NULL) // 1 time setup of garbage collection
    {
        Head = (struct Garbage*)malloc(sizeof(struct Garbage));
        Head->Unit = NULL;
        Head->Next = NULL;
    }
    
    struct Garbage *New = (struct Garbage*)malloc(sizeof(struct Garbage));
    New->Unit = unit;
    New->Next = NULL;
    Head->Next = New;
}

// Free up dynamically created memory
void Finalize()
{
    struct Garbage *current = Head; // setup for freeing loop. node
    while(current != NULL)          // free up each item in the list 
    {
        struct Garbage *temp = current; // prep item to be freeed
        current = current->Next;        // advance the current pointer
        free(temp->Unit);               // free up the item
        free(temp);                     // free up the container
    }
}

// splits the supplied string int a string array.
// assumption that text is a null terminated string.
void Split(char splitter, char *text, char ***strings, int *indexCount)
{
    int length;
    char *token = NULL, splitterToken[2] = { '\0', '\0' };
    *indexCount = 0;

    // create array the size of the char count
    *strings = (char **)malloc(sizeof(char*) * CharCount(text, splitter, strlen(text)));
    AddToFinalizeList(*strings); // track string array for garbage collection

    splitterToken[0] = splitter; // strtok requires a null-terminated string
    token = strtok(text, ",");   // split the string by the splitter character
    while (token != NULL)
    {
        // init string in array
        length = strlen(token);
        char* str = (char*)malloc(sizeof(char) * (length + 1));

        strncpy(str, token, length); // copy token to new string

        *(str + length) = '\0'; // make string null terminated
        AddToFinalizeList(str); // track new string for garbage collection

        *(*strings + *indexCount) = str; // save the string

        (*indexCount)++;            // advance the index count
        token = strtok(NULL, ",");  // advance the token
    }
}

// returns the count of the number of instance of the provided character in the string
int CharCount(char *string, char c, int length)
{
    int count = 0;
    
    // compare each character in the string and count the instances of c
    for (int i = 0; i < length; i++)
        if (*(string + i) == c)
            count++;
    
    return count;
}

// Counts the lines in the file
// It assumes the file is open, and will count the number of lines read from the position
// the position of the supplied file pointer will not be affected.
int LineCount(FILE *fptr)
{
    int count = 0;
    long pos = ftell(fptr); // get file current position
    char input;

    // count the number of lines
    while(fscanf(fptr, "%c", &input) != EOF)
        if (input == '\n')
            count++;

    // the line count is zero if the file is empty.    
    // adding for for the last/first line.
    if (pos != ftell(fptr))
        count++;

    // reset the pointer back to its original position
    fseek(fptr, pos, SEEK_SET); 

    return count;
}

// Removes leading and trailing whitespace characters.
char* Trim(char* str)
{
    int strLength = strlen(str);
    int front = 0, back = strLength - 1;
    
    // find last non whitespace character in the string
    while (isspace(str[back]) || str[back] == '\0') back--;
    
    // find first non whitespace character in the string
    while (isspace(str[front]) || str[front] == '\0') front++;
    
    int tLength = back - front + 1; // calc the length of the trimmed string
    
    // create copy buffer and add it to garbage collection
    char *t = (char*)malloc(sizeof(char) * tLength + 1);    
    AddToFinalizeList(t);
    
    // remove the whitespace from the front of the string.
    strncpy(t, (str + front), tLength);
    t[tLength] = '\0';
    
    return t;
}

// loads the student records into a linked list of Student type
void LoadDatabase(char *filename, struct Student **students)
{
    FILE *fptr = fopen(filename, "r");
    char line[1024];    

    *students = NULL; // init the list of students

    if (LineCount(fptr) == 0) // if the file is empty, you're done.  cheers!
    {   
        fclose(fptr);
        return;
    }

    bzero(line, 1024); // init the line buffer.
    
    while (fgets(line, 1024, fptr) != NULL) // reading the line.
    {   
        // split line, by the commas, into a string array
        char **strings = NULL;
        int cnt = 0;    
        Split(',', line, &strings, &cnt); 

        // skip the header row
        if (strcmp(*strings, "Name") != 0)
        {
            // create a new student record
            struct Student *newStudent = (struct Student*)malloc(sizeof(struct Student));

            // assign the array elements to the respective properties
            newStudent->Name = Trim(*strings);
            newStudent->Id = Trim(*(strings + 1));
            newStudent->Score = atof(*(strings + 2));

            newStudent->Next = *students;   // advance the list pointer
            *students = newStudent;         // set the head of the list to the new student
            AddToFinalizeList(newStudent);  // add the pointer to the garbage collector
        }

        bzero(line, 1024); // reset the line buffer                    
    }    
    
    fclose(fptr);
}

// Find and print the the student with the high score.
void FindHighScore(struct Student *students)
{
    struct Student *student = students, *current = students;
    
    while (current != NULL)  // iterate through the list.
    {   
        // set the student with the high score
        if (current->Score > student->Score)
            student = current;
        
        current = current->Next; // advance to the next node in the list
    }
    
    // print the student name and id.
    if (student != NULL)
        printf("The student with the high score is %s %s.\n", student->Name, student->Id);
}