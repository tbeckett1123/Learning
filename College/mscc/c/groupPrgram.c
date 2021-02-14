# include <stdio.h>
# include <string.h>
# define ROWS 10
# define COL 80

void loadData(char (*)[COL]);
void writeFile(char (*)[COL], char *);
void ASCIIseq(char (*)[COL]);
void strLen(char (*)[COL]);
void printfirst(char (*)[COL]);

void main()
	{
   char string[ROWS][COL];

   loadData(string);
	ASCIIseq(string);
	strLen(string);
	printfirst(string);
   }

void ASCIIseq(char (*Pstring)[COL])
	{

	int val, i, j;
   char temp[COL], *Ptemp, path[]="ASCIIsqec.txt";

   Ptemp = temp;

	for(i=0; i<ROWS; i++)
   	{
      for(j=0; j<ROWS; j++)
      	{
	   	val = strcmp( *(Pstring + i), *(Pstring + j));
         if(val < 0)
         	{
            strcpy(Ptemp, *((Pstring + i)+0));
            strcpy(((Pstring +i)+0), *((Pstring + j)+0));
            strcpy(((Pstring + j)+0), Ptemp);
            }
      	}
   	}
   writeFile(Pstring, path);
   }

void loadData(char (*string)[COL])
	{
   int i;
   static char path[]="list.txt", *pntr;
   FILE *fp;
   fp = fopen(path,"r");
   for(i=0; pntr = fgets(*((string + i)), 256, fp) != NULL; i++);
   fclose(fp);
   }

void writeFile(char (*string)[COL], char *path)
	{
   int i;
   FILE *fp;
   fp = fopen(path, "a");
   for(i=0; i<ROWS; i++)
   	fputs(*((string+i)), fp);
   fclose(fp);
   }

void strLen(char (*strptr)[COL])
{
	int i, j;
   char strsto[COL], *sptemp, Path[]="stringlength.txt";

   sptemp = strsto;

   for(i = 0; i < ROWS; i++)
   {
   	for(j = 0; j < ROWS; j++)
      {
      	if(strlen(*(strptr+i)) <= strlen(*(strptr+j)))
         {
         	strcpy(sptemp, (*(strptr+i)+0));
            strcpy((*(strptr+i)+0), (*(strptr+j)+0));
            strcpy((*(strptr+j)+0), sptemp);
         }
      }
   }
	writeFile(strptr, Path);
}

void printfirst(char (*s)[COL])
{
     int i, wordlength[ROWS], j, tempint;
     char space = ' ';
     char *start, temp[COL], *ptr, path[]="firstword.txt";


     for(i=0; i < ROWS; i++)
        {
        start = *(s + i);
        ptr = strchr(*(s + i), space);
        wordlength[i] = ptr- start;

        }

     for(i = 0; i < 3; i++)
      {
      	for (j = i + 1; j < ROWS; j++)
      		{
            	if(wordlength[i] > wordlength[j])
            		{
                  	 strcpy(temp , *(s + i));
                      tempint = wordlength[i];
                   	 strcpy(*(s + i) , *(s + j));
                      wordlength[i] = wordlength[j];
                   	 strcpy(*(s + j) , temp);
                      wordlength[j] = tempint;
               	}
         	}
      }
writeFile(s,path);
}
