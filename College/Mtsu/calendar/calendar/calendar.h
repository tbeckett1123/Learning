# include <iostream>
# include <fstream>
# include <iomanip>
# include <string>

using namespace std;

const string DOW[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

const struct Months
{
	Months()
	{
		MONTH[0].NOM   = "January";
		MONTH[0].DOM   = 31;
		MONTH[1].NOM   = "February";
		MONTH[1].DOM   = 28;
		MONTH[2].NOM   = "March";
		MONTH[2].DOM   = 31;
		MONTH[3].NOM   = "April";
		MONTH[3].DOM   = 30;
		MONTH[4].NOM   = "May";
		MONTH[4].DOM   = 31;
		MONTH[5].NOM   = "June";
		MONTH[5].DOM   = 30;
		MONTH[6].NOM   = "July";
		MONTH[6].DOM   = 31;
		MONTH[7].NOM   = "August";
		MONTH[7].DOM   = 31;
		MONTH[8].NOM   = "September";
		MONTH[8].DOM   = 30;
		MONTH[9].NOM   = "October";
		MONTH[9].DOM   = 31;
		MONTH[10].NOM  = "November";
		MONTH[10].DOM  = 30;
		MONTH[11].NOM  = "December";
		MONTH[11].DOM  = 31;
	}
	
	struct MonthType{string NOM; unsigned short int DOM;} MONTH[12];
}MOY;

const unsigned short int SD = 2;	//start date for the know peroid is 01-01-1980
					//this is the day of the week for the known start peroid
const unsigned long SY = 1980;		//this is the first year of the known period

class calendar
{
	public:
		calendar(const unsigned long& yr)
		{
			//int adder;
			
			year = yr;
			day = month = 1;
			
			sd = (365 * (yr - SY) + LeapYearCount() + SD) % 7;  
			//determining the starting day of the current period
			//this does the same as the tri-nested for loops below
			
			/*cout << sd << endl;
			
			sd = SD;	//dertermine the starting day of the current period
						
			for(int i = SY; i < yr; i++)
				for(int j = 0; j < 12; j++)
				{
					adder = (LeapYear(i) && j == 2) ? 1 : 0;
						
					
					for(int k = 0; k < MOY.MONTH[j].DOM + adder; k++)
					
						sd = (sd + 1) % 7;
				}
			
			cout << sd << endl;*/
			
			
		}
		
		calendar()
		{
			year = 1980;
			day = month = 1;
			sd = SD;
			
		}
	
		void ShowMonth(int mo)
		{
			mo--;
			
			if(mo > 11 || mo < 0)
			{
				cerr << "invalid month\n"
				     << "please enter a number from 1 to 12\n";
				
				return;
			}
			
			cout << left << MOY.MONTH[mo].NOM << endl
			     << setfill('-') << setw(70) << "-" << setfill(' ') << endl;
			     
			for(int i = 0; i < 7; i++)
				cout << left << setw(10) << DOW[i];
			cout << endl;

			int start = StartDay(mo);

			for(int i = 0; i < MOY.MONTH[mo].DOM + (LeapYear(year) && mo == 2) ? 1 : 0; i++)
			{
				start = (i == 0) ? start*10 : 10;
				cout << setw(start) << i+1;
				
				if((i+1) % 7 == 0)
					cout << endl;				
			}
			cout << endl;
		}
		
	private:			
		
		int StartDay(const int & mo)
		{	
			int start = sd;
		
			for(int i = 0; i < mo; i++)
				start = (start + MOY.MONTH[i].DOM + (mo == 2 && LeapYear(year)) ? 1 : 0) % 7;

			cout<< "startday = "<< start <<endl;

			return start;
		}

		int LeapYearCount()
		{
			int cnt = 0;
			
			for(long i = 1980; i < year + 1; i++)
				if(LeapYear(i))
					cnt++;
			
			return cnt;				
		}

		bool LeapYear(long year)
		{
			bool retval = false;
			
			if(year % 4 == 0)
			{
	 		  	if(year % 100 == 0)
				{
				    if(year % 400 == 0)
					retval = true;
			  	}
				else
					retval = true;
			
			}
			
			return retval;
		}
		

		unsigned long year,
		 	      month,
 		              day;
		unsigned short sd;

};
