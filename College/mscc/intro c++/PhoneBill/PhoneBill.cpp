# include <iostream.h>
# include <iomanip.h>
# include <stdio.h>
/*
       Program Name:	PhoneBill.exe
         Programmer:	Timothy Beckett
 	            Date:	2-18-02
 		     Language:	Borland C++
		    Flowchart:
		     Function:	This program take the distance, time, calculates the
							cost of each phone call, and prints out a statement.
             Inputs: Distance = D (miles), Length of time = T (minutes)
				Outputs:	Distance, Time, Cost
Other Programs Used:	N/A
  Data Restrictions: None
				 Method:	Get Distances,Get Times
             			Calculate Cost C = 0.30 (T + 0.05 * D)
							Print:	Heading
                     			Call	Distance	     Time     Cost
										  1	Da	      		Ta	      Ca
										  2	Db	      		Tb	      Cb
										  3	Dc	      		Tc	      Cc

         Looks Like:	Call    Distance        Time       Cost
							  1            3          20        6.05
							  2            2          15        4.53
							  3            6           4        1.29


*/
int main()
{
float Ca, Cb, Cc, Ta, Tb, Tc, Da, Db, Dc;
// Call 1
Ta = 20.0;
Da = 3.0;
Ca = 0.30 * (Ta + 0.05 * Da);

// Call 2
Tb = 15.0;
Db = 2.0;
Cb = 0.30 * (Tb + 0.05 * Db);

// Call 3
Tc = 4.0;
Dc = 6.0;
Cc = 0.30 * (Tc + 0.05 * Dc);

cout<<"Call"<<setw(12)<<"Distance"<<setw(12)<<"Time"<<setw(12)<<"Cost\n"
	 <<"  1 "<<setw(12)<<Da<<setw(12)<<Ta<<setw(12)<<setprecision(3)<<Ca<<endl
    <<"  2 "<<setw(12)<<Db<<setw(12)<<Tb<<setw(12)<<setprecision(3)<<Cb<<endl
    <<"  3 "<<setw(12)<<Dc<<setw(12)<<Tc<<setw(12)<<setprecision(3)<<Cc<<endl;

    getchar();
	 return 0;
}