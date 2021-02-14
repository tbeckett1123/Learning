// program to illustrate bisection method of finding root
// author: R. Detmer
// date: 9/14/05
// revised: 9/12/2006

#include <iostream>
#include <string>
using namespace std;

typedef float fctnType(float x);

float Bisection(fctnType f, float a, float b, int nMax, float epsilon)
// find root of f(x) between a and b to within epsilon, but limiting the number of iterations to nMax
// precondition: f(a) and f(b) have opposite signs
// returns root
{
	float c, fa, fb, fc, error;
	fa = f(a);
	fb = f(b);
	if (fa*fb > 0) throw exception("function has same sign at endpoints");
	error = abs(b-a);
	for (int n = 0; n < nMax; n++)
	{
		error = error/2;
		c = a + error;
		fc = f(c);
		// next line for debugging only
//		cout << n << "  " << c << "  " << fc << "  " << error << "  " << epsilon << endl;
		if (error < epsilon) return c;	// found an approximate root within epsilon
		if (fc == 0.0) return c;		// found an exact root
		
		// cut interval in half to continue
		if (fa*fc < 0)
		{
			b = c;
			fb = fc;
		}
		else
		{
			a = c;
			fa = fc;
		}
	}
	return (a + error/2);	// ran out of iterations; return best guess
}

float poly(float x)
// cubic polynomial with roots -1, 2 and 5
{
	return (x+1.0)*(x-2.0)*(x-5.0);
}


int main()
{
	float a, b, tolerance;
	int maxIterations;
	cout << "Left interval endpoint? ";
	cin >> a;
	cout << "Right interval endpoint? ";
	cin >> b;
	cout << "Maximum length of final interval? ";
	cin >> tolerance;
	cout << "Maximum number of iterations? ";
	cin >> maxIterations;
	cin.ignore(50, '\n');
	try
	{
		cout << "\nApproximate root: " << Bisection(poly, a, b, maxIterations, tolerance) << endl;
	}
	catch (exception &bisectError)
	{
		cout << "Error in Bisection: " << bisectError.what() << endl;
	}

	string holdScr;
    cout << "\npress Enter to continue";
    getline (cin, holdScr);

	return 0;
}
