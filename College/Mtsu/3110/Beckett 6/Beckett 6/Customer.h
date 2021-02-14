/*
Programmer:		Timothy Beckett
Class:			CSCI 3110
Instructor:		Dr. Seo
File:			Customer.h
*/
# include "Person.h"
# include "rbt.h"
# include "impRBT.cpp"
# include <fstream>
# include <string>
using namespace std;

# ifndef CUSTOMER_H
# define CUSTOMER_H
# define MAX_COUNT 10

class Customer: public Person
{
	friend istream& operator>>(istream&, Customer&);

public:

	Customer();
	
	bool operator<(const Customer&);
	bool operator>(const Customer&);
	bool operator==(const Customer&);
	bool operator!=(const Customer&);
	const Customer& operator=(const Customer&);

	string	acount_number;
	string list[MAX_COUNT];
};

# endif

