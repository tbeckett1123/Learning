//Programmer:			Timothy Beckett
//Class:				CSCI 3110
//Instructor:			Dr. Seo
//File:					Statistics.h
// *****************************************
//Description: The purpose of this struct is to
//combine two classes, TimeTracker and Counter
//into one data type for convience.

# include "Counter.h"
# include "TimeTracker.h"

# ifndef STATISTICS_H
# define STATISTICS_H

struct Statistics
{
	//See TimeTracker.h for methods and features
	//data protection is built into the class
	TimeTracker time_tracker;

	//See Counter.h for methods and features
	//data protection is built into the class
	Counter		counter;
};

# endif