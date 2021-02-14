/*
Programmer:	Timothy Beckett
Class:		CSCI 3110
Instructor:	Dr. Seo
*/
# include "SortedLinkedList.h"
# include "impSortedLinkedList.cpp"
# include "LinkedList.h"
# include "impSortedLinkedList.cpp"
# include "Person.h"
# include "Student.h"
# include "StudentWorker.h"
# include <fstream>

//function prototypes
void readFile(SortedLinkedList<Student*>&);
void editCourseGrade(SortedLinkedList<Student*>&);
void addCourse(SortedLinkedList<Student*>&);
void displayRecord(SortedLinkedList<Student*>&);
void addRecord(SortedLinkedList<Student*>&);
void displayAll(SortedLinkedList<Student*>&);

/*
	The main fucntion will display a menu to the user,
	get the users choice, and call the desired function.
	It will keep doing this till the user decides to quit

	Preconditions:	none
	Postconditions:	none
*/
int main()
{
	char choice;					//user selection
	SortedLinkedList<Student*> list;	//Student database

	readFile(list);

	do
	{
		system("cls");
		cout<<"1.	Display all students\n"
			<<"2.	add a student to the list\n"
			<<"3.	display a student record\n"
			<<"4.	edit a course grade\n"
			<<"5.	add course\n"
			<<"6.	quit\n";
		cin>>choice;

		switch(choice)
		{
			case '1':	displayAll(list); break;
			case '2':	addRecord(list); break;
			case '3':	displayRecord(list); break;
			case '4':	editCourseGrade(list); break;
			case '5':	addCourse(list); break;
			case '6':	cout<<" -- Goodbye --\n"; break;
			default:	cout<<"<--Invalid Selection-->\nPlease enter a number between 1 and 6\n";
						system("pause");
		};//end switch

	}while(choice != '6');

	return 0;
}
/*
This funciton read the data from the database file into
the SortedLinkedList.

Preconditions:	calling function must provide a list for
				storage
Postconditions:	the list will be populated into the pro-
				vided SortedLinkedList
*/
void readFile(SortedLinkedList<Student*>& ptrList)
{
	//function prototype
	void readRecord(Student**, ifstream&);

	ifstream file;
	Student* newRecord;
	string nfile;
	
	cout<<"Enter file name: ";	cin>>nfile;

	file.open(nfile.c_str());

	for(int tries = 0; !file; tries++)	//check for file open success
	{														//you have 5 tries to successfuly
		system("cls");										//open the file
		
		cerr<<"< - - - - - -  INVALID FILE NAME   - - - - - - >\n";

		if(tries>4)
		{
			cerr<<"you have exceeded the number of allowable attempts\n";
			exit(1);
		}//end if

		cerr<<"Enter file name: ";	cin>>nfile;

		file.open(nfile.c_str());
	}//end for

	readRecord(&newRecord, file);

	ptrList.ins(newRecord);

	while(!file.eof())
	{
		readRecord(&newRecord, file);
		ptrList.ins(newRecord);
	}//end while
	
	file.close();

}//end readFile


/*
This function will edit an existing student/worker course grade

Preconditions:	the calling function must provide a 
				SortedLinkedList<Student*> for storage
Postconditions:	the list will be edited; it will contain
				the new student/worker record
*/
void editCourseGrade(SortedLinkedList<Student*>& ptrList)
{
	Student *record;
	Course *course, *orgC;
	int index, i;
	string last, first;


	cout<<"Enter the last name: ";  cin>>last;
	cout<<"Enter the first name: "; cin>>first;

	record = new Student();

	record->setf(first);
	record->setl(last);

	if(ptrList.get(index, record))
	{
		delete record;
		ptrList.get(record, index);

		course = new Course();

		course->read();

		record->CourseList.get(i, course);
		record->CourseList.get(orgC, i);

		orgC->grade = course->grade;
		delete course;
	}
	else
	{
		cerr<<"Record not found\n";
		system("pause");
	}

}//end editCourseGrade

/*
This function will add a course to an existing student/worker

Preconditions:	the calling function must provide a 
				SortedLinkedList<Student*> for storage
Postconditions:	the list will be edited; it will contain
				the new student/worker record
*/
void addCourse(SortedLinkedList<Student*>& ptrList)
{
	Student *add;
	Course *course;
	string f, l;
	int i;

	cout<<"Enter the first name\n";
	cin>>f;

	cout<<"Enter the last name\n";
	cin>>l;

	add = new Student();

	add->setf(f);
	add->setl(l);

	if(ptrList.get(i, add))
	{
		delete add;

		ptrList.get(add, i);

		course = new Course();

		course->read();

		add->CourseList.ins(course);
	}
	else
	{
		cerr<<"Record not found\n";
		system("pause");
	}


}//end addCourse

/*
The function will print to the screen a student record

Preconditions:	the calling function must provide a
				SortedLinkedList<Student*> for searching
Postconditions:	none
*/
void displayRecord(SortedLinkedList<Student*>& ptrList)
{
	Student* display;
	string first, last;
	int i;

	cout<<"Enter Student's name(last first):\n";
	cin>>last>>first;

	display = new Student();
	display->setf(first);
	display->setl(last);

	if(ptrList.get(i, display))
	{
		delete display;
		ptrList.get(display, i);
		display->display();
	}
	else
		cerr<<"Record not found\n";
	
	system("pause");
}//end displayRecord

/*
This function will add a student/worker to the list

Preconditions:	The calling fucntion must provide a
				SortedLinkedList<Student*> for storage
Postconditions:	The new record will be add to the pro-
				vided list
*/
void addRecord(SortedLinkedList<Student*>& ptrList)
{
	Student* add;
	char choice;

	cout<<"do you wish to add a student for a student worker (s/w)\n";
	cin>>choice;

	switch(choice)
	{
	case 's': add = new Student();
			  add->read();
			  ptrList.ins(add);
			  break;
	case 'w': add = new StudentWorker();
			  add->read();
			  ptrList.ins(add);
			  break;
	default:  cerr<<"Invalid Selection\n";
			  system("pause");
	};
	
}//end addRecord

/*
This fucntion will display all the recordes
in the list

Preconditions:	the calling function must provide
				a SortedLinkedList<Student*> for
				traversing
Postconditions:	none
*/
void displayAll(SortedLinkedList<Student*>& ptrList)
{
	Student *record;

	for(int i = 0; i < ptrList.size(); i++)
	{
		ptrList.get(record, i);
		
		cout<<*record<<endl;
		
		if(i%3 == 0  && i > 0)
			system("pause");
	}

	system("pause");
}//end displayAll

/*
This function is a sub function of read File.
It reads the char and creates the appropriate
record type, then it reads the record from
the file and puts it into the object.

Preconditions:	the calling function must pro-
				vide the address to a pointer
				to Student type and an opened
				file.
Postconditions:	the provided pointer will
				point to a record of Student/
				StudentWorker type which will
				be intialized to a Student/
				StudentWorker.
*/
void readRecord(Student** buf, ifstream& file)
{
	char select;
	Student *getS;
	StudentWorker *getW;

	file>>select;

	
	switch(select)
	{
	case 's':	getS = new Student();
				file>>*getS;
				*buf = getS;
				break;
	case 'w':	getW = new StudentWorker();
				file>>*getW;
				*buf = getW;
				break;
	default:	cerr<<"< - - INVALID DATA - - >\n";
				exit(1);
	};

}//end readRecord