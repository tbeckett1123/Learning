/*
Programmer:	Timothy Beckett
File:		impStudent.h -- Student Class
Class:		CSCI 3110
Instructor:	Dr. Seo
*/

# include "Student.h"
# include "impSortedLinkedList.cpp"

// * * * * Constructors * * * *

//defualt constructor
Student::Student()
{
	gpa = 0.0;
}//end defualt constructor

//copy constructor
Student::Student(Student& org): Person(org.first, org.last, org.ssn)
{
	gpa = org.gpa;
	Course* buf;

	for(int index = 0; index < org.CourseList.size(); index++)
	{
		org.CourseList.get(buf, index);
		CourseList.ins(buf);
	}//end for
}//end copy constructor

//initialize constructor
Student::Student(string iLast, string iFirst, int iSsn,
				 float iGpa, SortedLinkedList<Course*> iCourseList)
				 : Person(iFirst, iLast, iSsn)
{
	gpa = iGpa;
	
	Course* buf;

	for(int i = 0; i < iCourseList.size(); i++)
	{
		iCourseList.get(buf, i);
		CourseList.ins(buf);
	}//end for
}// end initialize constructor

// * * * * friend functions * * * * 

ostream& operator<<(ostream& out, Student & printer)
{
	Course* cPrint;
	int i;

	out <<left
		<<printer.last<<endl
		<<printer.first<<endl
		<<printer.ssn<<endl
		<<fixed<<setprecision(3)<<printer.gpa;

	for(i = 0; i < printer.CourseList.size(); i++)
	{
		printer.CourseList.get(cPrint, i);
		if(i%2 == 0)
			out<<endl;
		out <<cPrint->dept<<" "<<cPrint->num<<" "<<cPrint->grade<<" ";
	}//end for
	if(i%2 == 0)
		out<<endl;

	return out;
}//end operator <<

istream& operator>>(istream& in, Student& geter)
{
	Course dummy;

	in  >>geter.last
		>>geter.first
		>>geter.ssn
		>>geter.gpa;
	
	//Enter 'quit' to stop entering courses
	Course *c = &dummy;
	
	for(c->dept = "go"; c->dept != "quit"; )
	{
		c = new Course();
		//enter dept
		in>>c->dept;

		if(c->dept != "quit")
		{
			//enter the id number
			in>>c->num;
			//enter the final grade
			in>>c->grade;
			
			geter.CourseList.ins(c);
		}//end if

	}//end for

	return in;
}//end operator >>

// * * * * class methods * * * *

bool Student::getg(float & buf)
{
	if(gpa == NULL || gpa == 0.0)
		return false;

	buf = gpa;

	return true;
}//end getg

void Student::setg(const float & newGpa)
{
	gpa = newGpa;
}//end setg

// * * * * virtual methods * * * * 

void Student::display()
{
	 cout<<left
		 <<setw(10)<<first
		 <<setw(10)<<last
		 <<setw(10)<<ssn
		 <<setw(10)<<fixed<<setprecision(3)<<gpa
		 <<right;
	
	Course* cPrint;
	int i;
	for(i = 0; i < CourseList.size(); i++)
	{
		CourseList.get(cPrint, i);
		if(i%2 == 0)
			cout<<endl;
		cPrint->print();
	}//end for

	if(i%2 == 0)
		cout<<endl;
}//end display

void Student::read()
{
	 cout<<"Enter the first name: ";
	 cin>>first;
	 cout<<"Enter the last name: ";
	 cin>>last;
	 cout<<"Enter the Social Security Number: ";
	 cin>>ssn;
	 cout<<"Enter the Grade Point Average: ";
	 cin>>gpa;

	cout<<"Enter quit for the dept to stop entering courses\n";
	Course *c = new Course();
	
	for(c->dept = "go"; c->dept != "quit"; )
	{
		cout<<"enter the dept: ";
		cin>>c->dept;

		if(c->dept != "quit")
		{
			cout<<"enter the id number: ";
			cin>>c->num;

			CourseList.ins(c);
		}//end if
	}//end for


}//end read

char Student::id()
{return 's';}

// * * * * Overloaded Operators * * * * 

bool Student::operator <(const Student& rValue)
{
	if(last < rValue.last || last == rValue.last && first < rValue.first)
		return true;

	return false;
}//end operator <

bool Student::operator==(const Student& rValue)
{
	if(last == rValue.last && first == rValue.first)
		return true;

	return false;
}//end operator ==

 Student& Student::operator=(Student& rValue)
{
	last = rValue.last;
	first = rValue.first;
	ssn = rValue.ssn;
	gpa = rValue.gpa;

	Course* buf;

	for(int index = 0; index < rValue.CourseList.size(); index++)
	{
		rValue.CourseList.get(buf, index);
		CourseList.ins(buf);
	}//end for
	
	return rValue;
}//end operator =