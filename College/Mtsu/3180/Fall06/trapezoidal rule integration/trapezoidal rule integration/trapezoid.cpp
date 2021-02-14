// test iterative trapezoidal rule integration algorithm
// author: R. Detmer
// date: 10/12/05

#include <iostream>
#include <cmath>
using namespace std;

float f(float x)
// f(x) := cos(x) * x^(1/2)
{
	return sqrt(x)*cos(x);
}

int main()
{
	int nbrIterations;
	float h;
	float a;
	float b;
	int twoPower;
	float sum;
	float R[100];

	cout << "left endpoint? ";
	cin >> a;
	cout << "right endpoint? ";
	cin >> b;
	cout << "number of iterations? ";
	cin >> nbrIterations;

	h = b-a;
	R[0] = h*(f(a)+f(b))/2.0;
	twoPower = 1;
	for (int row=1; row<=nbrIterations; row++)
	{
		twoPower *= 2;
		h /= 2.0;
		sum = 0.0;
		for (int k=1; k<=twoPower-1; k+=2) sum += f(a+k*h);
		R[row] = 0.5*R[row-1] + h*sum;
	}

	cout << "\napproximations to integral:" << endl;
	for (int row=0; row<=nbrIterations; row++)
	{
		cout << R[row] << endl;
	}
	return 0;
}