# include <iostream.h>
# include <iomanip.h>
# include <stdio.h>
# include <conio.h>

void main ()
	{
	//prototypes
	void extend(double[], double[],double[],int);
	void getItem(double[], double[], int&);
   void print(double[],double[],int);
	//end of prototypes

	double price[10], quantity[10], amount[10];
	int count = 0;

   getItem(price, quantity, count);
   print(price, quantity, count);
	getchar();
	}

void getItem(double price[], double quantity[], int& count)
	{
	char done = 'n';
   while (done == 'n')
	   {
      if (count < 11)
      	{
	   	cout<<"enter the price";cin>>price[count];
		   cout<<"enter the quantity";cin>>quantity[count];
   		count++;
		   cout<<"do you want to enter another item(y/n)";cin>>done;
   		}
      }
	}
void print(double price[], double quantity[], int count)
	{
   for (int i = 0; i < count; i++)
   	{
      cout<<price[i]<<quantity[i]<<endl;
      }
   }