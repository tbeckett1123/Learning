# include <iostream.h>
# include <iomanip.h>
# include <stdio.h>
# include <math.h>


int main()
{

float E,I,M;

I = .06;
M = 4.0;
E = pow((1 + I / M),M)-1;


cout	<<"The Effective Annual Rate is"
      <<setw(7)<<setprecision(4)<< (E * 100)
      <<" %"<<endl
      <<"When stated rate is"
      <<setw(5)<<setprecision(4)<< (I * 100)
      <<" %"<<endl
      <<"and it is compounded"<<setw(4)<<M<<" times a year";

getchar();
return 0;
//program by Tim Beckett
}
