/*
Programmer:	Timothy Beckett
File:		impStudentWorker.cpp -- StudentWorker Class
Class:		CSCI 3110
Instructor:	Dr. Seo
*/

# include "StudentWorker.h"

// * * * * Friend Functions * * * *

ostream& operator<<(ostream& out, StudentWorker& printer)
{
	Course *cPrint;
	int i;

	printer.Gpa();
	
	out <<left
		<<printer.last<<endl
		<<printer.first<<endl
		<<printer.ssn<<endl
		<<fixed<<setprecision(3)<<printer.gpa<<endl
		<<fixed<<setprecision(2)<<printer.rate<<endl
		<<fixed<<setprecision(2)<<printer.hours<<endl;
		
	for(i = 0; i < printer.CourseList.Size(); i++)
	{
		printer.CourseList.get(cPrint, i);

		out <<cPrint->dept<<" "<<cPrint->num<<" "<<cPrint->grade<<" "<<endl;
	}//end for

	return out;
}//end operator <<

istream& operator>>(istream& in, StudentWorker& geter)
{
	in  >>geter.last
		>>geter.first
		>>geter.ssn
		>>geter.gpa
		>>geter.rate
		>>geter.hours;
	
	//Enter 'quit' for dept to stop entering courses
	Course *c, *d;

	d = c = new Course();

	for(c->dept = "go"; c->dept != "quit"; )
	{
		c = new Course();
		//enter the dept
		in>>c->dept;

		if(c->dept != "quit")
		{
			//enter the id number
			in>>c->num;
			//enter the final grade:
			in>>c->hours;
			//enter hours hours earned/atempted
			in>>c->grade;
			
			geter.CourseList.ins(c);
		}//end if
	}//end for

	delete d;//used d to keep from having a memory leek

	return in;
}//end operator >>

// * * * * Constructors * * * * 

//default constructor
StudentWorker::StudentWorker()
{
	rate = hours = salary = 0.0;

}//end default constructor

//copy constructor
StudentWorker::StudentWorker(const StudentWorker &org)
{
	salary = org.salary;
	rate = org.rate;
	hours = org.hours;
}//end copy constructor

//initialize constructor
StudentWorker::StudentWorker(string f, string l, int s,
							 float r, float h,
							 SortedLinkedList<Course*> list)
{
	rate = r;
	hours = h;
	calcSal();
}//end initialize constructor

// * * * * protected method * * * *

void StudentWorker::calcSal()
{
		salary = rate * hours;
}//end calcSal

// * * * * class methods * * * *

float StudentWorker::Salary()
{
	calcSal();
	return salary;
}//end getSal

// * * * * virtual methods * * * * 

void StudentWorker::display()
{
	 Salary();		//calculate salary and gpa
	 Gpa();			//just in case :-)

	 cout<<left
		 <<setw(10)<<last.substr(0,8)
		 <<setw(10)<<first.substr(0,8)
		 <<setw(11)<<ssn
		 <<setw(8)<<fixed<<setprecision(3)<<gpa
		 <<setw(8)<<fixed<<setprecision(2)<<rate
		 <<setw(8)<<fixed<<setprecision(2)<<hours
		 <<fixed<<setprecision(2)<<salary
		 <<right<<endl;
}//end display

void StudentWorker::read()
{
	 cout<<"Enter the first name: ";
	 cin>>first;
	 cout<<"Enter the last name: ";
	 cin>>last;
	 cout<<"Enter the Social Security Number: ";
	 cin>>ssn;
	 cout<<"Enter the Gpa: ";
	 cin>>gpa;
	 cout<<"Enter the Pay Rate: ";
	 cin>>rate;
	 cout<<"Enter the Hours Worked: ";
	 cin>>hours;

	cout<<"To stop entering courses\n"
		<<"Enter quit for the dept\n"
		<<"Enter 1111 for the id number\n"
		<<"Enter E for the Grade\n"
		<<"Enter 0 for the hours\n"; 
	Course *c;

	c = new Course();

	for(c->dept = "go"; c->dept != "quit"; )
	{
		c->read();

		if(c->dept != "quit")
		{
			CourseList.ins(c);
		}//end if
	}//end for
}//end read

char StudentWorker::id()
{return 'w';}

// * * * * Overloaded Operators * * * *

bool StudentWorker::operator <(const StudentWorker & rValue)
{
	if(last < rValue.last || last == rValue.last && first < rValue.first)
		return true;

	return false;
}//end operator<

bool StudentWorker::operator==(const StudentWorker& rValue)
{
	if(last == rValue.last && first == rValue.first)
		return true;

	return false;
}//end operator ==

StudentWorker& StudentWorker::operator=(StudentWorker& rValue)
{
	last = rValue.last;
	first = rValue.first;
	ssn = rValue.ssn;
	gpa = rValue.gpa;
	rate = rValue.rate;
	hours = rValue.hours;

	Course *buf;

	for(int index = 0; index < rValue.CourseList.Size(); index++)
	{
		rValue.CourseList.get(buf, index);
		CourseList.ins(buf);
	}//end for
	
	return rValue;
}//end operator =