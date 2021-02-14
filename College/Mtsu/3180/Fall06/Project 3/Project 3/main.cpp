/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	Programmer:		Timothy Beckett													   *
 *	Date:			10/20/2006														   *	
 *	Purpose:		This program will take the equation in the function Integrand and  *	
 *					aprproximate its intergral based on the user provided interval,	   *
 *					tolerance, and max number of interation allowed  				   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

# include <iostream>
# include <cmath>

using namespace std;

typedef float fctntype(float x);

float Integrand(float x);			// This is the fucntion that is to be integrated


									// adaptive Simpson's rule integration
float Simpson(fctntype	f,			// f:float->float - function to be integrated
			  float		a,			// [a, b] - interval of integration
			  float		b, 
			  float		epsilon,	// epsilon - tolerance
			  int		level,		// level - recursive depth (always call with 0 from main)
			  int		levelMax);	// levelMax - maximum allowed recursive depth before throwing 
									// exception with what = "maximum level exceeded in Simpson"



int main()
{
	float a,			//starting interval
		  b,			//stopping interval
		  epsilon;		//tolerance
	int	  levelMax;		//maximum allowed interations

	cout << "Enter the starting interval\n";
	cin	 >> a;

	cout << "Enter the stopping interval\n";
	cin  >> b;

	cout << "Enter the tolerance\n";
	cin  >> epsilon;

	cout << "Enter the maxium number of interations\n";
	cin	 >> levelMax;
	
	cout << "The integral for cos(2x)e^(-x) is aproximately ";

	try
	{
		cout << Simpson(Integrand, a, b, epsilon, 0, levelMax) << endl;
	}
	catch(exception& e)
	{
		cout << "\nERROR: " << e.what() << endl;
	}

	return 0;
}



// This is the fucntion that is to be integrated
float Integrand(float x)
{
	//		cos(2x)e^-x
	return	float(cos( 2.0f * x ) * exp( -1.0f * x ));
}



// adaptive Simpson's rule integration
// f:float->float - function to be integrated
// [a, b] - interval of integration
// epsilon - tolerance
// level - recursive depth (always call with 0 from main)
// levelMax - maximum allowed recursive depth before throwing exception
// with what = "maximum level exceeded in Simpson"
float Simpson(fctntype f, float a, float b, float epsilon, int level, int levelMax)
{
	if(level > levelMax) //check if count exceeds max number of interations
		throw( exception("The maxium number of interations has been reached\n") );

	level++; //increment count	
	
	float	c = (a + b) * .5f;
	float	h = b - a;
	float	one_simpson = h / 6.0f * ( f(a) + 4.0f * f(c) + f(b) );
	float	d = (a + c) * .5f;
	float	e = (c + b) * .5f;
	float	two_simpson = h / 12.0f * ( f(a) + 4.0f * f(d) + 2.0f * f(c) + 4.0f * f(e) + f(b) );
	float	dif_simpson = two_simpson - one_simpson;
	float	result;

	if(fabs(dif_simpson) < 15.0f * epsilon)
	{
		result = two_simpson + dif_simpson / 15.0f;
	}
	else
	{
		result = Simpson(f, a, c, epsilon / 2.0f, level, levelMax) + Simpson(f, c, b, epsilon / 2.0f, level, levelMax);
	}
	
	return result;
}