/*
       Program Name:	Array.exe
         Programmer:	Timothy Beckett
 	            Date:	4-16-02
 		     Language:	Borland C++
		    Flowchart:
           For main:
  		      Function:	This program call 4 functions and loops the program
            				also, it passes the apropreate arraies to these functions
              Inputs:   more
             Outputs:	printed statement - "Do you want to make other table?"
 Other Programs Used:	getItem()
								extend()
   	                  sort()
      	               print()
   Data Restrictions:	N/A
  		  For getItem:
  		      Function:	This program gets the price and quantity on hand and
            				loops the program until the user says to stop looping or
                        the arraies are full.
              Inputs:   more, price[1] - price[10], quantity[1] - quantity[10]
				 Outputs:	printed statements- "Enter Item:"
             										- "Enter Price:"
                                          - "Enter Quantity:"
             										- "Do you want to enter other item?"
 Other Programs Used:	N/A
  		  For extend:
  		      Function:	This program take the price and quantity of each item
            				and caclulates the total amount for each item.
              Inputs:   price[1] - price[x], quantity[1] - quantity[x],
              				amount[1] - amount[x]
				 Outputs:	N/A
 Other Programs Used:	N/A
   		  For sort:
  		      Function:	This program sorts the amounts from greast to smallest
            				and shifts price and quantity to stay with their amount
              Inputs:   price[1] - price[x], quantity[1] - quantity[x],
              				amount[1] - amount[x]
				 Outputs:	N/A
 Other Programs Used:	N/A
  		    For print:
  		      Function:	This program prints out all data enter into the arries
               Inputs:   price[1] - price[x], quantity[1] - quantity[x],
              				amount[1]- amount[x]
				 Outputs:	printed statement - "amount price quantity"
             				amount[1] - amount[x], price[1] - price[x],
                        quantity[1] - quantity[x]
 Other Programs Used:	N/A
*/



# include <iostream.h>
# include <iomanip.h>
# include <conio.h>
# include <stdio.h>

void getItem(double[], double[], int&);
void extend(double[], double[],double[],int);
void sort(double[], double[],double[],int);
void print(double[], double[], double[], int);

void main ()
	{
	char more;
	double price[10], quantity[10], amount[10];
   int count;

	do
   	{
      count = 0;
      getItem(price, quantity, count);
   	extend(price, quantity, amount, count);
	   sort(price, quantity, amount, count);
      cout<<setiosflags(ios::showpoint)<<setiosflags(ios::fixed)
   		 <<setprecision(2);
      print(price, quantity, amount, count);
      cout<<"Do you want to create another table (y/n)?";cin>>more;
      clrscr();
      }
   while (more != 'n');
   }


void getItem(double price[], double quantity[], int& count)
	{
	char more;
   do
	   {
      if (count <= 9)
      	{
	   	cout<<"enter item:\n"<<"enter the price:";cin>>price[count];
		   cout<<"enter the quantity:";cin>>quantity[count];
   		count++;
		   cout<<"do you want to enter another item(y/n)";cin>>more;
         }
      else
      	{
         more = 'n';
         cout<<"because you have entered 10 items,you can not enter any more values";
         getchar();
			}
      clrscr();
      }
   while (more == 'y');
	}


void extend(double price[], double quantity[], double amount[], int count)
	{
   for (int multiplier = 0; multiplier < count; multiplier++)
   	amount[multiplier] = price[multiplier] * quantity[multiplier];
	}


void sort(double price[], double quantity[], double amount[], int count)
	{
   double temp;
   for (int control = 0; control < count; control++)
		{
      for (int compare = control + 1; compare < count; compare++)
      	{
         if (amount[control] < amount [compare])
         	{
            temp = amount[control];
            amount[control] = amount[compare];
            amount[compare] = temp;

            temp = price[control];
            price[control] = price[compare];
            price[compare] = temp;

            temp = quantity[control];
            quantity[control] = quantity[compare];
            quantity[compare] = temp;
            }
         }
      }
   }

void print(double price[], double quantity[], double amount[], int count)
	{
   	cout<<setw(8)<<"amount"<<setw(8)<<"price"<<setw(12)<<"quantity\n";
  		for (int print = 0; print < count; print++)
  		{
      cout<<setw(8)<<amount[print]<<setw(8)<<price[print]<<setw(10)
	       <<quantity[print]<<endl;
     	}
   }
