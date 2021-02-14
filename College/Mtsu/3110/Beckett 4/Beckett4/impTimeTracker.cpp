/*
Programmer:		Timothy Beckett
Class:			CSCI 3110
Instructor:		Dr. Seo
File:			impTimeTracker.cpp
*/

# include "TimeTracker.h"

void TimeTracker::Start()
{
	start_time = time(NULL);	
}

void TimeTracker::Stop()
{
	stop_time = time(NULL);
}

void TimeTracker::CalculateLapse()
{
	lapse_time = difftime(stop_time, start_time);
}

time_t TimeTracker::StartTime()
{
	return start_time;
}

time_t TimeTracker::StopTime()
{
	return stop_time;
}

double TimeTracker::TimeLapse()
{
	return lapse_time;
}

char* TimeTracker::CStartTime()
{
	char *cstart = new char [15];
	tm * tm_start;

	tm_start = localtime(&start_time);

	strftime(cstart, 15, "%H:%M:%S", tm_start);
	
	return cstart;
}

char* TimeTracker::CStopTime()
{
	char *cstop = new char [15];
	tm * tm_stop;

	tm_stop = localtime(&stop_time);

	strftime(cstop, 15, "%H:%M:%S", tm_stop);
	
	return cstop;
}


