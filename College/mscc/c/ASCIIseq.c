# include <stdio.h>
# include <string.h>
# define ROWS 10
# define COL 80
void  main()
	{
   void printSarray(char (*)[COL]), loadData(char (*)[COL]), writeFile(char (*)[COL], char *);
	int val, i, j;
   char string[ROWS][COL], (*Pstring)[COL], temp[COL], *Ptemp, path[]="ASCIIsqec.txt";
   Pstring = string;
   Ptemp = temp;
   loadData(string);
   printSarray(string);
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
   printSarray(string);
   writeFile(string, path);
   getchar();
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

void printSarray(char (*string)[COL])
	{
   int i;

   for(i=0; i<ROWS; i++)
   	printf("%s", (string + i));
   }
