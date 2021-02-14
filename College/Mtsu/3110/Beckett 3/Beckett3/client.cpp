/*
Programmer:	Timothy Beckett
Class:		CSCI 3110
File:		client.cpp
Instructor:	Dr. Seo
------------------------------------------------
This program displays a menu to the user.
It gives the options to edit a course grade,
add a course, display a record, add a record,
and display all records.
The student records are read from a file before
the menu is displayed.
*/
# include "SortedLinkedList.h"
# include "impSortedLinkedList.cpp"
# include "StudentWorker.h"
# include <fstream>

//function prototypes
void readFile(SortedLinkedList<StudentWorker*>&);
void editCourseGrade(SortedLinkedList<StudentWorker*>&);
void addCourse(SortedLinkedList<StudentWorker*>&);
void displayRecord(SortedLinkedList<StudentWorker*>&);
void addRecord(SortedLinkedList<StudentWorker*>&);
void displayAll(SortedLinkedList<StudentWorker*>&);

/*
	The main fucntion will display a menu to the user,
	get the users choice, and call the desired function.
	It will keep doing this till the user decides to quit

	Preconditions:	none
	Postconditions:	none
*/
int main()
{
	char choice;							//user selection
	SortedLinkedList<StudentWorker*> the_list;	//Student database

	readFile(the_list);

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
			case '1':	displayAll(the_list); break;
			case '2':	addRecord(the_list); break;
			case '3':	displayRecord(the_list); break;
			case '4':	editCourseGrade(the_list); break;
			case '5':	addCourse(the_list); break;
			case '6':	cout<<" -- Goodbye --\n"; break;
			default:	cout<<"<--Invalid Selection-->\nPlease enter a number between 1 and 6\n";
						system("pause");
		};//end switch

	}while(choice != '6');

	return 0;
}

void readFile(SortedLinkedList<StudentWorker*>& ptrList)
{
	ifstream file;
	string name;
	StudentWorker *temp;
	//Read data from file input.dat
	//data ordering:
	//		last name
	//		first name
	//		social security number
    //		grade point average
	//		pay rate
	//		hours worked
	//		course work (transcript)
	//			department
	//			class id
	//			grade
	//			hours
	//			* end of data signal
	//				"quit"

	//Open file
	//		check for success
	//			if failure -- repeat 5 time 
	//				prompt for correct file name
	cout<<"enter the file name: "; cin>>name;
	file.open(name.c_str());

	for(int i = 0; !file; i++)
	{
		if(i > 4)
			exit(1);

		cout<<"invalid file name -- enter the file name: ";
		cin>>name;
		file.clear();
		file.open(name.c_str());
	}

	//Read in each record and insert it into the
	//list until eof is encountered
	//		get Student information
	//			use overloaded operator >> and a StudentWorker
	//		insert record into list
	//			use SortedLinkedList method ins(T&, const int&)
	do{
		temp = new StudentWorker();
		file>>*temp;

		ptrList.ins(temp);
	}while(!file.eof());

	file.close();
}//readFile

void editCourseGrade(SortedLinkedList<StudentWorker*>& ptrList)
{
	StudentWorker *ac;
	Course *ec;
	int i, j;

	ac = new StudentWorker();

	//Get Student Name
	cout<<"Enter the student name: "; cin>>ac->last>>ac->first;
	//Get index from the list
	ptrList.get(i, ac);
	//Get Student record from the list with the provided index
	delete ac;
	ptrList.get(ac, i);
	//Remove the student from the list
	ptrList.rem(ac);
	//Get the dept and course number of the course to be edited
	ec = new Course();
	cout<<"enter the course dept and id: ";
	cin>>ec->dept>>ec->num;
	//Get the index of the course to be edited from the course list
	ac->CourseList.get(j, ec);
	//Get the course record from the course list
	delete ec;
	ac->CourseList.get(ec, j);
	//Remove the course from the course list
	ac->CourseList.rem(ec);
	//Change Grade
	cout<<"enter the new grade: ";
	cin>>ec->grade;
	//Add course back to course list
	ac->CourseList.ins(ec);
	//Add the Student back into the list
	ptrList.ins(ac);
}//editCourseGrade

void addCourse(SortedLinkedList<StudentWorker*>& ptrList)
{
	StudentWorker *sr;
	Course *nc;
	int i;

	sr = new StudentWorker();

	//Get the student name of the record to be edited
	cout<<"enter the student name: ";
	cin>>sr->last>>sr->first;
	//Get the index of the record from the list
	ptrList.get(i, sr);
	//Get the record from the list
	ptrList.get(sr, i);
	//Remove the student from the list
	ptrList.rem(sr);
	//Get the course info for the course record
	nc = new Course();	
	nc->read();
	//Add course to the course list
	sr->CourseList.ins(nc);
	//add student record back into the list
	ptrList.ins(sr);
}//end addCourse

void displayRecord(SortedLinkedList<StudentWorker*>& ptrList)
{
	StudentWorker *dr;
	int index;

	dr = new StudentWorker();
	//Get student name
	cout<<"Enter the Student Name: "; cin>>dr->last>>dr->first;

	
	ptrList.get(index, dr);//Get index of record from the list
	ptrList.get(dr, index);//Get the record with the index provided by list

	//Display StudentWorker info
	cout<<*dr<<endl;

	system("pause");

}//end displayRecord

void addRecord(SortedLinkedList<StudentWorker*>& ptrList)
{
	StudentWorker *add;

	add = new StudentWorker();

	//get student worker information
	cout<<"Enter the last name, first name, ssn, gpa, rate, hours, and\n"
		<<"the courses (enter the dept, course number, credits, and grade)\n"
		<<"enter quit to stop entering courses\n";
	cin>>*add;

	//add to list
	ptrList.ins(add);
}//end addRecord

void displayAll(SortedLinkedList<StudentWorker*>& ptrList)
{
	StudentWorker *printer;

	cout<<left
		<<setw(10)<<"Last"<<setw(10)<<"First"<<setw(11)<<"SSN"
		<<setw(8)<<"GPA"<<setw(8)<<"Rate"<<setw(8)<<"Hours"
		<<"Salary"<<endl<<right
		<<setfill('-')<<setw(61)<<'-'<<setfill(' ')<<endl;

	for(int i = 0; i < ptrList.Size(); ++i)
	{
		ptrList.get(printer, i);
		printer->display();
	}//end for loop -- print loop

	system("pause");
}//end displayAll
