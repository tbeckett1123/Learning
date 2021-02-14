/*
	Programer:		Timothy Beckett
	Date:			10-04-06
	Program Purpose:
	
	The purpose of this program is to estimate
	the x value that will make the provided
	funciton go to zero ie f(x) ~= 0.
*/

# include <iostream>
# include <iomanip>
# include <string>
# include <cmath>

using namespace std;


/*****************************************************************************
This is creating a type for the desired function for fltSecant and vdCalcFofX.
******************************************************************************/
typedef float FctnType(float X);


/*************************************************************************************************
	This function calculates the value for x that will make the provided polynomial  go to zero.
**************************************************************************************************/
float Secant(FctnType		Fctn,	//Function whose zero is to be approximated
				float		x1,		//Starting guess 1
				float		x2,		//Starting guess 2
				float		epsi,	//Quit if two successive x values are this close
				float		delta,	//Quit if a function value is this close to 0
				int			maxf);	//Maximun number of function evaluations allowed





//This is the function to be evaluated by fltSecant
float TheFunction(float x);

	
int main()
{
	float	x1, x2, epsi, delta;
	int		maxf;

	cout << "Enter the first starting guess: ";
	cin  >> x1;

	cout << "Enter the second starting guess: ";
	cin	 >> x2;

	cout << "Stop looping if two successive x values are this close. \nEnter this value: ";
	cin  >> epsi;

	cout << "Stop looping if a function value is this close to 0. \nEnter this value: ";
	cin  >> delta;

	cout << "Enter the maxium number of times the secant method may be applied\n";
	cin  >> maxf;


	cout << "The x intersect for e^x - 3x^2 is ";

	try
	{
		cout << fixed << /*setprecision(5) <<*/ Secant(TheFunction, x1, x2, epsi, delta, maxf) << endl;
	}
	catch(exception &e)
	{
		cout << e.what() << endl;	
	}

	return 0;
}

//This is the function to be evaluated by Secant
float TheFunction(float x)
{
	//			  e^x - 3x^2
	return float( exp(x) - 3 * x*x );
}

/*************************************************************************************************
	This function calculates the value for x that will make the provided polynomial  go to zero.
**************************************************************************************************/
float Secant(FctnType		Fctn,	//Function whose zero is to be approximated
				float		x1,		//Starting guess 1
				float		x2,		//Starting guess 2
				float		epsi,	//Quit if two successive x values are this close
				float		delta,	//Quit if a function value is this close to 0
				int			maxf)	//Maximun number of function evaluations allowed
{
	if(!maxf)
		throw exception("Maxium number of interations has been reached");

	float fx1 = Fctn(x1);
	float fx2 = Fctn(x2);
			
	if(!(fx1 - fx2 || x1 - x2))
		throw exception("An invalid slope has occured");

	float retValue, fx3, x3, temp;

	//calculate new x******************************

	x3 = x2 - (x2 - x1) / (fx2 - fx1) * fx2;

	fx3 = Fctn(x3);
	
	//*********************************************
	
	if( fx3 < epsi && fx3 < (fx2 + delta) && fx3 > (fx2 - delta) )
		retValue = x3;
	else
	{

		if( fabs(fx1) > fabs(fx2) )  //this puts the larger value in x2
		{							 //so to keep the smaller value on next iteration

			temp = x2;	//swap the x -values
			x2 = x1;
			x1 = temp;
		}

		x2 = x1;
		x1 = x3;

		//preform Secant method again with new x value
		retValue = Secant(Fctn, x1, x2, epsi, delta, maxf-1);

	}

	return retValue;
}
