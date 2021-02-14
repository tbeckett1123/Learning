/*
Programmer:		Timothy Beckett
Class:			CSCI 3110
Instructor:		Dr. Seo
File:			Customer.cpp
*/

# include "Customer.h"

# ifndef IMPCUSTOMER_CPP
# define IMPCUSTOMER_CPP

istream& operator>>(istream& in, Customer& writer)
{
	string temp;

	in	>>writer.acount_number
		>>writer.first
		>>writer.last;
		
	in>>temp;

	for(int i = 0; i < MAX_COUNT && (temp != "quit"); ++i)
	{
		writer.list[i] = temp;
			
		in>>temp;
	}

	return in;
}

//********* Cosntructors *************
Customer::Customer()
{
	first = last = acount_number = "empty";
	ssn = 0;
	for(int i = 0; i < MAX_COUNT; ++i)	list[i] = "empty";
}

bool Customer::operator <(const Customer & rValue)
{return (acount_number < rValue.acount_number);}

bool Customer::operator >(const Customer & rValue)
{return (acount_number > rValue.acount_number);}

bool Customer::operator ==(const Customer & rValue)
{return (acount_number == rValue.acount_number);}

bool Customer::operator !=(const Customer& rValue)
{return (acount_number != rValue.acount_number);}

const Customer& Customer::operator=(const Customer& org)
{
	first = org.first;
	
	last = org.last;

	acount_number = org.acount_number;

	for(int i = 0; i < MAX_COUNT; ++i)
		list[i] = org.list[i];

	return org;
}
#endif