/*
Program Name:		Classifier.exe
Programmer:			Timothy Beckett
Date:					5-02-02
Language:			Borland C++

main()
function:			Main calls 4 functions getData, classify, sort, and print
						it declairs an array of Applicants called information and
                  sets a pointer called info to point to information
inputs:				NA
outputs:				NA

getData()
function:			This function opens a file called camp.txt.  It then loops
						till the end of the file placing data into a varibale
                  called info wich point to information
                  it also count the number of times the function loops
inputs:				*info is passed to it by the function that calls it
outputs:				returns the value of count to the calling function

classify()
function:			This function assigns the weight class to each applicant in
						information based on that applicant's weight
                  it also counts up the number of lightweights, middleweights,
                  and heavyweights
inputs:           *info is passed to it by the function that calls it
                  count is passed to it by the calling function
                  &light, &middle, and &heavey are passed by the calling
                  function
outputs:				NA
sort()
function:			This function alphabetizes the records in *info by the
						string15 last if the last from (info +i) and the last from
                  (info + j) are the same then it compare the string first
                  if the those are the same then it sets count = 0 and stops
                  alphabetizing the records
inputs:				*info and &count are passed by the calling function
outputs:				the user is prompted that there is a duplicate entery in
						camp.txt if (info + i)->first and (info +j)->first are the
                  same
print()
function:			This function print to the screen and in a file called
						applicants.txt: *(info) through *(info + count), the total
                  number of light weight, the total number of middle weights,
                  the total number of heavy weight, and the total number of all
                  the applicants in each weight class
inputs:				*info, count, light, middle, heavy are passed by the calling
						function
outputs:				*(info) through *(info + count), light, middle, and heavy

*/
# include <iostream.h>
# include <fstream.h>
# include <iomanip.h>
# include <stdio.h>
# include <string.h>


typedef char string15[14];

struct Applicant
	{
   string15 first;
   string15 last;
   float weight;
   string15 weightClass;
   };

int getData (Applicant*);
void classify (Applicant*, int, int&, int&, int&);
void sort (Applicant*, int&);
void print (Applicant*, int, int, int, int);

void main ()
	{
   int count, light = 0, middle = 0, heavy = 0;
   Applicant information[20], *info;
   info = &information[0];

   count = getData(info);
   classify(info, count, light, middle, heavy);
	sort(info, count);
   print(info, count, light, middle, heavy);
   getchar();
	}

int getData(Applicant *info)
	{
   int count = 0;
   ifstream fin;

   fin.open("camp.txt", ios::nocreate);

   while (!fin.eof())
   	{
       fin>>info->last>>info->first>>info->weight;
       if (!fin.eof())
       count++;
       info++;
      }
	fin.close();
   return count;
   }

void classify(Applicant *info, int count, int& light, int& middle, int& heavy)
	{

   for (int i = 0; i < count; i++)
   	{
      if (info->weight < 100)
      	{
         strcpy(info->weightClass,"Lightweight");
			light++;
         }
      else if (info->weight < 200)
      	{
         strcpy(info->weightClass,"Middleweight");
			middle++;
         }
      else
      	{
         strcpy(info->weightClass,"Heavyweight");
			heavy++;
         }
      info++;
      }
	}

void sort(Applicant *info, int &count)
	{
   int move;
   Applicant temp;

   for (int i = 0; i < count; i++)
   	{
		for (int j = i+1; j < count; j++)
      	{

      	move = strcmp((info+i)->last, (info + j)->last);

      	if (move > 0)
      		{
       		temp = *(info + i);
       		*(info + i) = *(info + j);
       		*(info + j) = temp;
      		}
         else if (move == 0)
         	{
            move = strcmp((info+i)->first, (info + j)->first);

            if (move > 0)
      			{
       			temp = *(info + i);
      	 		*(info + i) = *(info + j);
   	    		*(info + j) = temp;
	            }
            else if (move == 0)
            	{
               cout<<"you have a double entry in camp.txt\n"
               	 <<"delete one "<<(info+i)->last<<" "<<(info + i)->first
                 	 <<" "<<(info + i)->weight<<" entry from the file";
               j = count;
               i = count;
               count = 0;
               }
         	}
         }
      }
   }

void print(Applicant *info, int count, int light, int middle, int heavy)
	{
   ofstream fout;
   if (count != 0)
   	{
   	fout.open("applicants.txt");
   	cout<<setw(12)<<"Name"<<setw(11)<<"Weight"<<setw(15)<<"Weight Class\n";
   	fout<<setw(12)<<"Name"<<setw(11)<<"Weight"<<setw(15)<<"Weight Class\n";
   	for (int i = 0; i < count; i++)
			{
   		cout<<setw(8)<<info->last<<setw(8)<<info->first<<setw(5)<<info->weight
      		 <<setw(16)<<info->weightClass<<endl;
   		fout<<setw(8)<<info->last<<setw(8)<<info->first<<setw(5)<<info->weight
      		 <<setw(16)<<info->weightClass<<endl;

	   	info++;
   		}
   	cout<<endl
   		 <<"Total number of lightweights is "<<light<<endl
   	 	 <<"Total number of middleweights is "<<middle<<endl
       	 <<"Total number of heavyweights is "<<heavy<<endl
      	 <<endl
      	 <<"Total number of all weight classes is "<<(light + middle + heavy)
      	 <<endl
      	 <<endl
      	 <<"A copy of this data is in applicants.txt\n";
   	fout<<endl
   		 <<"Total number of lightweights is "<<light<<endl
   		 <<"Total number of middleweights is "<<middle<<endl
      	 <<"Total number of heavyweights is "<<heavy<<endl
      	 <<endl
       	 <<"Total number of all weight classes is "<<(light + middle + heavy)
          <<endl;
   	fout.close();
      }
	}
