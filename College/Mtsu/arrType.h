# include <iostream>

using namespace std;

/*************************************************************************************
This data type will handle dynamic array sizeing see struct line comments for details
about how it operates.
**************************************************************************************/
# ifndef ARR_TYPE
# define ARR_TYPE
template <typename T>
struct arrType
{
public:

	//array intial size is one
	//the array is not initialized
	arrType()
	{
		intSize = 1;
		PtrArray = new T[1];
	}

	//destructor
	~arrType()
	{
		delete[] PtrArray;
	}

	//returns the size of the array
	int Size() //returns the size of the array
	{return intSize;}

	//returns desired array index value
	T& operator[](const int& intRefINDEX)
	{
		return PtrArray[intRefINDEX];
	}

	//This overloaded operator is used as an insert operator
	//the array size will be increased by one
	//all data in the array will be maintained and the new value will be added.
	//example:
	//arrType atArray;
	  ////atArray.Size 1;
	  ////atArray[0](value) ????
	//atArray = 10;
      ////atArray.Size 2;
	  ////atArray[0](value) ????	
	  ////atArray[1](value) 10
	////The array will insert a new index and stor the value 10 in it
	const T& operator=(const T& RefINITIAL_VALUE)
	{		
		T* PtrTemp = new T[intSize+1]; //create new arrray of intSize
		
		int intI;

		for(intI = 0; intI < intSize; intI++) //copy the contents of the old array into the new
			PtrTemp[intI] = PtrArray[intI];

		PtrTemp[intI] = RefINITIAL_VALUE; //add new value to the new array

		delete[] PtrArray; //destroy old array

		PtrArray = PtrTemp; //save new array address

		intSize++;	//increase the size of the array

		return RefINITIAL_VALUE;
	}

private:

	T* PtrArray; //this pointer stores the array
	int intSize;
};
#endif