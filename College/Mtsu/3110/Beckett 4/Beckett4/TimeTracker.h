//Programmer:		Timothy Beckett
//Class:			CSCI 3110
//Instructor:		Dr. Seo
//File:				TimeTracker.h
// **********************************************
//Description:	The purpose of this class is to
//track the amount of time it takes an algorith
//to run.  It provides data protection for the 
//start, stop, annd lapsed times.  The methods
//available are Start which gets the system time
//at the start of the algorith run.  Stop which
//gets the system time at the algorithm's completion.
//TimeLapse which will calculate the lapsed time
//between Start and Stop.  There are, also, two
//methods that return time_t types StartTime and
//StopTime. There is one method that returns a double
//TimeLapse; there are two methods the return char* 
//CStartTime and CStopTime.

# include <iostream>
# include <time.h>

using namespace std;

# ifndef TIMETRACKER_H
# define TIMETRACKER_H

class TimeTracker
{
public:
	//This method get the current time when 
	//an algorithm's run is started
	//Preconditions:	None
	//Postconditions:	The system time at
	//					the time of Start
	//					call will be stored
	void Start();

	//This method gets the current time when
	//an algorithm's run is completed
	//Preconditions:	None
	//Postconditions:	The system time at
	//					the time of Stop
	//					call will be stored
	void Stop();

	//This method will calculate the Lapsed
	//time from Start to Stop
	//Preconditions:	Start and Stop must
	//					have been run.
	//Postconditions:	The lapsed will be
	//					calculated
	void CalculateLapse();

	//This method returns the start time
	//Preconditions:	The Start method must
	//					have been used
	//Postconditions:	This method will return
	//					The Starting time.
	time_t StartTime();

	//This method will return the stoping time
	//Preconditions:	The Stop method must
	//					have been used
	//Postconditions:	This method will return
	//					The Stoping time.
	time_t StopTime();

	//This method will return the the lapsed time
	//from start to stop.
	//Preconditions:	The CalculateLapse method
	//					must have been used
	//Postconditions:	This method will return
	//					The Lapsed time
	double TimeLapse();

	//This method returns the start time as a cstring
	//Preconditions:	The Start method must
	//					have been used
	//Postconditions:	This method will return
	//					The Starting time in cstring form.
	char* CStartTime();
	
	//This method will return the stoping time as a cstring
	//Preconditions:	The Stop method must
	//					have been used
	//Postconditions:	This method will return
	//					The Stoping time in a cstring form.	
	char* CStopTime();
	
private:
	time_t start_time,
		   stop_time;
	double lapse_time;
};

# endif