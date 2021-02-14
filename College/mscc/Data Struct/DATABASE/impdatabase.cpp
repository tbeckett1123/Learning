# include "linklist.h";
/*
this function sets up the listed list from a file or from the user's input
the file is not found.
*/
linkedList::linkedList()
	{
   nodeType temp;
   home.record.listSize=0;
   previous = current = &home;
   home.nextNode = NULL;
   ifstream fIn;
   fIn.open("database.dat", ios::nocreate);
   if(fIn.fail())
   	{
   	getData();
      update();
      }
   else
   	{
      while(!fIn.eof())
      	{
         fIn.read((unsigned char *)&temp.data, sizeof temp.data);
         makeNode(temp);
         }
      }
   fIn.close();
   }
/* this function destroies the linked list and frees up memory
 when the program shuts down*/
linkedList::~linkedList()
	{
   reset();
  	for(int i = 0; i < home.record.listSize; i++)
  		{
		previous = current;
  	   current = current->nextNode;
     	delete previous;
      }
   }
/* this function checks to see if the linked list is empty*/
bool linkedList::empty()
	{
   if(home.record.listSize == 0)
   	return true;
   else
   	return false;
   }

/*this function lest you edit a student record
the user must select the feilds to be edited*/
void linkedList::editNode(int tempSSN)
	{
   char fieldList[8], correct;
   nodeType tempData;
   viewNode(tempSSN);
   tempData.data = current->record.data;
   cout<<"press return if paused here\n";
   getchar();
   cout<<"field numbers:\n"
   	 <<"1-name\n"
   	 <<"2-ssn\n"
       <<"3-faculty code\n"
       <<"4-lyr\n"
   	 <<"5-age\n"
       <<"6-sex\n"
       <<"7-marital status\n"
       <<"enter the number for every field you want to edit before you press enter\n"
       <<"(example:  if you want to edit name, ssn, and age. you would enter"
       <<" 125\n):";
   gets(fieldList);

   for(int i = 0; i < strlen(fieldList); i++)
   	{
      clrscr();
      switch(fieldList[i])
      	{
         case '1': cout<<"Name(format: last name, first name): ";
                   gets(tempData.data.name);
         			 break;
         case '2': cout<<"ssn: ";
         			 cin>>tempData.data.ssn;
                   break;
         case '3': cout<<"faculty code(e,m,h,o): ";
         			 cin>>tempData.data.facultyCode;
                   tempData.data.facultyCode = toupper(tempData.data.facultyCode);
                   break;
         case '4': cout<<"last year registered(4 digit year): ";
         			 cin>>tempData.data.lyr;
         			 break;
         case '5': cout<<"age: ";
         			 cin>>tempData.data.age;
         			 break;
         case '6': cout<<"sex(m/f): ";
         			 cin>>tempData.data.sex;
                   tempData.data.sex = toupper(tempData.data.sex);
         			 break;
         case '7': cout<<"marital status(s, m, w, d): ";
         			 cin>>tempData.data.stat;
                   tempData.data.stat = toupper(tempData.data.stat);
         			 break;
         default: cout<<"* * * * * invalid selction * * * * *\n";
         };
      }

/*varafies the data changes are correct if they are then the changes are saved
to the linked list but not to the file if they are not correct then the
editNode() is called again to correct the changes unless the user say to exit*/
   printf("   Name: %s \n    SSN: %d \nFaculty: %c \n    age: %d \n    sex: %c   \n    LYR: %d \n   STAT: %c\n\n", tempData.data.name, tempData.data.ssn, tempData.data.facultyCode, tempData.data.age, tempData.data.sex, tempData.data.lyr, tempData.data.stat);
   cout<<"are the changes correct(y/n/e-exit edit): ";cin>>correct;
   correct = toupper(correct);
   if(correct == 'Y')
   	current->record.data = tempData.data;
   else if(correct == 'N')
   	editNode(tempSSN);
   else
   	cout<<"data changes where not verified and will not be saved\n";
   }
/* this function will take a record of nodeType,  create a node, and insert it
into the linked list*/
void linkedList::makeNode(nodeType tempData)
	{
   nodePtr temp;
   if(search(tempData.data.ssn))
     	cout<<"this record already exists\n";
   else
   {
   search(tempData.data.name);
   if(empty())
   	{
      current = new node();
      current->nextNode = NULL;
      home.nextNode = current;
      reset();
      }
   else if(current == home.nextNode)
   	{
      if(strcmp(tempData.data.name, current->record.data.name)>0)
			{
         previous = current;
         current = new node();
         current->nextNode = previous->nextNode;
			previous->nextNode = current;
         }
      else
			{
         current = new node();
	      current->nextNode = home.nextNode;
   	   home.nextNode = current;
      	reset();
         }
      }
   else if(current->nextNode == NULL)
   	{
      if(strcmp(tempData.data.name, current->record.data.name)>0)
      	{
         previous = current;
		   current = new node();
   		previous->nextNode = current;
      	current->nextNode = NULL;
         }
      else
      	{
         current = new node();
         current->nextNode = previous->nextNode;
         previous->nextNode = current;
         }
      }
   else
   	{
      temp = current;
      current = new node();
      current->nextNode = temp;
      previous->nextNode = current;
      }
   current->record.data = tempData.data;
   home.record.listSize++;
   }
   }

// this function sets all node pointers to the front of the linked list
void linkedList::reset()
	{
   previous = current = home.nextNode;
   }
/* this function deletes a record form the linked list if the student has not
has not register for at least two years*/
void linkedList::delNode(int tempSSN)
	{
    bool delFlag = false;
    date curntDate;
    getdate(&curntDate);
    int year;
    reset();
    search(tempSSN);
    year = curntDate.da_year - current->record.data.lyr;
    if(year < 3)
    	cout<<"You may not delete this record until the person has not registered"
      	 <<" for 2 years.\n";
	else if(current == home.nextNode)
    	{
		home.nextNode = current->nextNode;
      delete current;
      delFlag = true;
      }
    else if(current->nextNode == NULL)
    	{
		delete current;
      current = previous;
      current->nextNode = NULL;
      delFlag = true;
      }
    else
    	{
      previous->nextNode = current->nextNode;
      delete current;
      current = previous->nextNode;
      delFlag = true;
      }
    if(delFlag == true)
	    home.record.listSize--;
   }
// this function will view a stundent record and will find it by ssn
void linkedList::viewNode(int tempData)
	{
   clrscr();
   search(tempData);
   print();
   }
// this function finds and displays all records the have the same facaulty code
void linkedList::viewNode(char tempData)
	{
   clrscr();
   reset();
   tempData = toupper(tempData);
   if(empty())
   	{}
   else
   {
   for(int i = 0; i < home.record.listSize; i++)
   	{
	   if(current->record.data.facultyCode == tempData)
	   	printf("Name: %s SSN: %d\n",current->record.data.name, current->record.data.ssn);
   	current = current->nextNode;
      }
   }
   }
// the function prints the entire database to the screen
void linkedList::viewAll()
	{
   clrscr();
   reset();
   for(int i = 1; i <= home.record.listSize; i++)
   	{
      cout<<"Record "<<i<<endl;
      print();
      previous = current;
     	current = current->nextNode;
      }
   }
// this function is used by other function to print records to the screen
void linkedList::print()const
	{
   printf("   Name: %s \n    SSN: %d \nFaculty: %c \n    age: %d \n    sex: %c \n    LYR: %d \n   STAT: %c \n\n", current->record.data.name, current->record.data.ssn, current->record.data.facultyCode, current->record.data.age, current->record.data.sex, current->record.data.lyr, current->record.data.stat);
   }
// this function updates the database file with changes made to the linked list
void linkedList::update()
	{
   ofstream fOut;
   fOut.open("database.dat", ios::trunc | ios::binary);
   reset();
   for(int c = 1; c <= home.record.listSize; c++)
   	{
	   fOut.write((unsigned char*)&current->record, sizeof current->record);
      current = current->nextNode;
      }
   fOut.close();
   }
/* this function gets the student information and calls makeNode() to insert
the record into the linked list*/
void linkedList::getData()
	{
   char tempChar;
   nodeType tempData;
   char again = 'Y';
   cout<<"press return if paused here\n";
   getchar();
   do
   	{
      clrscr();
	   cout<<"name(format: Last Name, First Name): ";
	   gets(tempData.data.name);
	   cout<<"\nssn: ";
	   cin>>tempData.data.ssn;
	   cout<<"\nfaculty code(e, m, h, o): ";
      cin>>tempChar;
	   tempData.data.facultyCode  = toupper(tempChar);
	   cout<<"\nlast year registered(4 digit year): ";
	   cin>>tempData.data.lyr;
	   cout<<"\nage: ";
	   cin>>tempData.data.age;
	   cout<<"\nsex(m/f): ";
      cin>>tempChar;
	   tempData.data.sex = toupper(tempChar);
	   cout<<"\nmarital status(s, m, w, d): ";
      cin>>tempChar;
	   tempData.data.stat = toupper(tempChar);
   	cout<<"\nenter another record?(y/n): ";
      cin>>tempChar;
   	again = toupper(tempChar);
   	makeNode(tempData);
   	}
   while(again == 'Y');
   }
// this function searches the linked list to find a record by ssn
bool linkedList::search(int temp)
	{
   bool foundIt;
   nodePtr tempNode;
   if(empty())
   	{
      foundIt = false;
      }
   else
   {
   reset();
   for(int i = 0;current->record.data.ssn != temp && i < home.record.listSize;)
   	{
      foundIt = true;
      if(current->nextNode != NULL)
      	{
	      tempNode = current;
   	   current = current->nextNode;
      	previous = tempNode;
         }
      else
      	{
         i = home.record.listSize;
         foundIt = false;
         }
      }
   }
   return foundIt;
   }
//this function search the linked list to find the location to insert a new node
void linkedList::search(char *temp)
	{
   nodePtr tempNode;
   if(empty())
		{}
   else
   {
   reset();
   for(int i = 0;strcmp(temp, current->record.data.name) > 0 && i < home.record.listSize;)
   	{
      if(current->nextNode != NULL)
      	{
	      tempNode = current;
   	   current = current->nextNode;
      	previous = tempNode;
			}
      else i = home.record.listSize;
      }
   }
   }
// this function prints a menu for the user to choose from
void home()
	{
   clrscr();
   cout<<"I -- make a new student record\n" //getData()
    	 <<"D -- delete a student record (you may only delete a student who has not registerd for two years)\n" //delNode(int)
       <<"M -- modify a student record\n" // editNode(int)
       <<"P -- display a student record\n" // viewNode(int)
       <<"L -- display a list of all students by faculty code\n" //viewNode(char)
       <<"E -- display the entire database\n" // viewAll()
       <<"U -- udate the database file\n" // update()
       <<"Q -- quit\n"
       <<"enter your selection:";
   }
/* this function calls the nessary functions to do the work needed based on the
users choice or it sets exit to TRUE*/
bool action(char actionCode, linkedList &dataBase)
	{
   int ssn; char code;
   bool exit = false;
   actionCode = toupper(actionCode);
   clrscr();
   switch(actionCode)
   	{
      case'I': dataBase.getData();
      			break;
      case'D': cout<<"enter student's ssn: "; cin>>ssn;
      			dataBase.delNode(ssn);
               break;
      case'M': cout<<"enter student's ssn: "; cin>>ssn;
					dataBase.editNode(ssn);
      			break;
      case'P': cout<<"enter student's ssn: "; cin>>ssn;
               dataBase.viewNode(ssn);
      			break;
      case'L': cout<<"enter the faculty code: "; cin>>code;
               dataBase.viewNode(code);
      			break;
      case'E': dataBase.viewAll();
      			break;
      case'U': dataBase.update();
      			break;
      case'Q': exit = true; break;
      default: cout<<"* * * * * * * INVALID SELECTION * * * * * *\n";
      }
      system("PAUSE");
   return exit;
   }


