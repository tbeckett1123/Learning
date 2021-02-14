/*
Programmer:	Timothy Beckett
Class:		CSCI 3110
Instructor:	Dr. Seo
*/
# include "Person.h"

// * * * * constructors * * * *

//default constructor
Person::Person()
{
	first = last = "nobody";
	ssn = 0;
}//end default

//copy constructor
Person::Person(const Person & org)
{
	first = org.first;
	last = org.last;
	ssn = org.ssn;
}//end copier

//initialize constructor
Person::Person(const string& fn, const string& ln, const int& ss)
{
	first = fn;
	last = ln;
	ssn = ss;
}//end intializer

// * * * * class methods * * * *

//get the first name
bool Person::getf(string& ptrFirst)
{
	if(first == "nobody")
		return false;
	
	ptrFirst = first;

	return true;
}//end get first name

//get the last name
//use defined word LAST to select method
bool Person::getl(string & ptrLast)
{
	if(last == "nobody")
		return false;

	ptrLast = last;

	return true;
}//end get last name

//get the ssn
bool Person::gets(int & ptrSSN)
{
	if(ssn == 0)
		return false;

	ptrSSN = ssn;

	return true;
}//end get ssn

//set first name
void Person::setf(const string & newFirst)
{
	first = newFirst;
}//end set first name

//set last name
//use defined word LAST
void Person::setl(const string & newLast)
{
	last = newLast;
}//end set last name

//set ssn
void Person::sets(const int & newSSN)
{
	ssn = newSSN;
}//end set ssn

//set Salary

//overloaded == operator will return true if the names are the same
bool Person::operator ==(const Person & rValue)
{
	if(first == rValue.first && last == rValue.last)
		return true;

	return false;
}//end operator ==

//overload = operator will copy the the rValue into the lValue object
 const Person& Person::operator=(const Person & rValue)
{
	first = rValue.first;
	last = rValue.last;
	ssn = rValue.ssn;

	return rValue;
}//end operator =

 //overload < operator will compare and return a bool
 bool Person::operator<(Person & rValue) const
 {
		
	if(last < rValue.last || ((last == rValue.last) && (first < rValue.first)))
		return true;

	return false;
 }//end < operator

// * * * * virtual methods * * * *

//This method displays the Personal information
 void Person::display()
 {
	 cout<<left
		 <<first<<endl
		 <<last<<endl
		 <<ssn<<endl
		 <<right;
 }//end display

//This method gets the Personal information
//and stores it in the object
 void Person::read()
 {
	 cout<<"Enter the first name: ";
	 cin>>first;
	 cout<<"Enter the last name: ";
	 cin>>last;
	 cout<<"Enter the Social Security Number: ";
	 cin>>ssn;

 }//end read

 char Person::id()
 {return 'p';}

// * * * * friend functions * * * * 

//overloaded operators << and >>
ostream& operator<<(ostream& out, const Person& printer)
{
	out	<<left
		<<printer.last
		<<printer.first
		<<printer.ssn
		<<endl<<right;
	return out;
}//end operator <<

istream& operator>>(istream& in, Person& writer)
{
	in >>writer.last;
	in >>writer.first;
	in >>writer.ssn;
	return in;
}//end operator >>