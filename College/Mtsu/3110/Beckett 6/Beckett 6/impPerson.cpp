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
	in >>writer.ssn;
	in >>writer.first;
	in >>writer.last;
	
	
	return in;
}//end operator >>