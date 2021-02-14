# include <stdio.h>
# include <iomanip.h>
# include <string.h>
# include <conio.h>
# include <stdlib.h>
# include <ctype.h>
# include <fstream.h>
# include <dos.h>

union nodeType
	{
	struct
		{
	   char name[21]; // Last name then first name
   	int ssn;
	   char facultyCode; /*faculty codes
    							  E-English
   							  M-Math
         	              H-History
            	           O-Other
   							*/
	   int lyr; // last year registered
   	int age;
	   char sex;// M-male or F-female
   	char stat;// S-single, M-married, W-widowed, D-devorced
	   }data;
   int listSize;
   };
struct node;
typedef node* nodePtr;
struct node
	{
   nodeType record;
   nodePtr nextNode;
   };

class linkedList
	{
   private:	node home;
            nodePtr previous, current;
            bool search(int), empty();
            void search(char*), print()const, reset();

   public:	linkedList();
   			~linkedList();
            void makeNode(nodeType), delNode(int), editNode(int);
            void viewNode(int), viewAll(), viewNode(char), update();
            void getData();
   };


