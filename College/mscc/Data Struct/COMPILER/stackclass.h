#include <iomanip.h>;
#include <stdlib.h>;
const int capacity = 128;
const int bottom = 0;
const int reset = -1;
template <typename stackType>
class StackVar
	{
   private:
   stackType theStack[capacity];
   int top;

   public:
   StackVar();
   void push(stackType), clear();
   bool empty();
   stackType pop(), peek();
   };
template <typename stackType>
StackVar<stackType>::StackVar()
	{
   top = reset;
   }
template <typename stackType>
void StackVar<stackType>::push(stackType temp)
	{
    if(top <= capacity)
    	{
	    top++;
   	 theStack[top] = temp;
      }
    else cout<<"the Stack is full\n";
   }
template <typename stackType>
void StackVar<stackType>::clear()
	{
   top = reset;
   }
template <typename stackType>
bool StackVar<stackType>::empty()
	{
   if(top >= bottom)
      return false;
   else
	   return true;
   }
template <typename stackType>
stackType StackVar<stackType>::pop()
	{
   stackType temp;
   if(!empty())
   	{
   	temp = theStack[top];
   	top--;
      }
   else
   	{
      exit(1);
      }
   return temp;
   }
template <typename stackType>
stackType StackVar<stackType>::peek()
	{
   if(!empty())
   	return theStack[top];
   else
   	exit(1);

   }

