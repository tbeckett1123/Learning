// illustrate Horner's polynomial evaluation
// author: R. Detmer
// date: 8/30/2007

#include <iostream>
using namespace std;

float horner(float a[], int n, float x);
// evaluate a[0] + a[1]*x + a[2]*x^2 + ... + a[n]*x^n using Horner's method

int main()
{
   float a[] = {-5, 1, -7, 2, 3};
   cout << "p(1) = " << horner(a, 4, 1) << endl;
   cout << "p(1.5) = " << horner(a, 4, 1.5) << endl;
   return 0;
}

float horner(float a[], int n, float x)
// evaluate a[0] + a[1]*x + a[2]*x^2 + ... + a[n]*x^n using Horner's method
{
   float value = a[n];
   for (int i=n-1; i>=0; i--)
   {
      value = value*x + a[i];
   }
   return value;
}

