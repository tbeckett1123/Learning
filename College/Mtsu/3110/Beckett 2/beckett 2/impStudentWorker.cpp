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
	Course* cPrint;
	int i;

	out <<left
		<<printer.last<<endl
		<<printer.first<<endl
		<<printer.ssn<<endl
		<<fixed<<setprecision(3)<<printer.gpa<<endl
		<<fixed<<setprecision(2)<<printer.hours<<endl
		<<fixed<<setprecision(2)<<printer.rate<<endl;

		
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

istream& operator>>(istream& in, StudentWorker& geter)
{
	Course dummy;

	in  >>geter.last
		>>geter.first
		>>geter.ssn
		>>geter.gpa
		>>geter.hours
		>>geter.rate;
	
	//Enter 'quit' for dept to stop entering courses
	Course *c = &dummy;
	
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
			in>>c->grade;
			
			geter.CourseList.ins(c);
		}//end if

	}//end for

	return in;
}//end operator >>

// * * * * Constructors * * * * 

//default constructor
StudentWorker::StudentWorker()
{
	rate = hours = salary = 0.0;
	doCalc = false;
}//end default constructor

//copy constructor
StudentWorker::StudentWorker(StudentWorker &org)
	//: Student(org.last, org.first, org.ssn, org.gpa, org.CourseList)
{
	doCalc = org.doCalc;
	salary = org.salary;
	rate = org.rate;
	hours = org.hours;
}//end copy constructor

//initialize constructor
StudentWorker::StudentWorker(string f, string l, int s,
							 float g,
							 float r, float h,
							 SortedLinkedList<Course*> list)
							 //: Student(f,l,s,g,list)
{
	doCalc = true;
	rate = r;
	hours = h;
	salary = 0.0;
}//end initialize constructor

// * * * * protected method * * * *

void StudentWorker::calcSal()
{
		doCalc = false;
		salary = rate * hours;
}//end calcSal

// * * * * class methods * * * *

bool StudentWorker::getr(float& buf)
{
	if(rate > .0000000001)
	{
		buf = rate;
		return true;
	}//end if

	return false;
}//end getr

bool StudentWorker::geth(float& buf)
{
	if(hours > .0000000001)
	{
		buf = hours;
		return true;
	}//end if

	return false;
}//end geth

bool StudentWorker::getSal(float& buf)
{
	if(doCalc) calcSal();
	if(salary > .00000001) 
	{
		buf = salary;
		return true;
	}//end if
	return false;
}//end getSal

void StudentWorker::setr(float buf)
{
	doCalc = true;
	rate = buf;
}//end setr

void StudentWorker::seth(float buf)
{
	doCalc = true;
	hours = buf;
}//end seth

// * * * * virtual methods * * * * 

void StudentWorker::display()
{
	 calcSal();

	 cout<<left
		 <<setw(10)<<first
		 <<setw(10)<<last
		 <<setw(10)<<ssn
		 <<setw(10)<<fixed<<setprecision(3)<<gpa<<endl
		 <<setw(10)<<fixed<<setprecision(2)<<rate
		 <<setw(10)<<fixed<<setprecision(2)<<hours
		 <<setw(10)<<fixed<<setprecision(2)<<salary
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

void StudentWorker::read()
{
	 cout<<"Enter the first name: ";
	 cin>>first;
	 cout<<"Enter the last name: ";
	 cin>>last;
	 cout<<"Enter the Social Security Number: ";
	 cin>>ssn;
	 cout<<"Enter the Grade Point Average: ";
	 cin>>gpa;
	 cout<<"Enter the Pay Rate: ";
	 cin>>rate;
	 cout<<"Enter the Hours Worked: ";
	 cin>>hours;

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
	doCalc = rValue.doCalc;
	rate = rValue.rate;
	hours = rValue.hours;

	Course* buf = new Course();

	for(int index = 0; index < rValue.CourseList.size(); index++)
	{
		rValue.CourseList.get(buf, index);
		CourseList.ins(buf);
	}//end for
	
	return rValue;
}//end operator =