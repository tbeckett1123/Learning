/* Programmer:	Timothy Beckett
 * Homework:	4
 * Due:		Friday March 2, 2007
 * Instructor:	Dr. Li
 * * * * * * * * * * * * * * * * * */
# include <iostream>
# include <iomanip>
# include <cmath>

using namespace std;

// *************** DATA TYPES ***********************

template <typename T>
class arrType
{
public:
	arrType();
	~arrType();
	int Size();
	T& operator[](const int& intRefINDEX);
	const T& operator=(const T& RefINITIAL_VALUE);
private:
	T* PtrArray; //this pointer stores the array
	int intSize;
};

class vector_t
{
	friend ostream& operator<<(ostream& out, vector_t data);
public:	
	
	vector_t(double initAngle);			//default constructor
	vector_t operator+(vector_t& rhs); 	
	const vector_t& operator=(const vector_t& rhs);	
	double magnitude;  				//centimenters
	double angle();	   				//degrees
	double rangle();				//randians
	double cos_angle();				//sin, cos, and tan are in radians
	double sin_angle();
	double tan_angle();
private:
	double ang; 					//degrees
	double rang;					//radians
	double cos_ang, sin_ang, tan_ang;
};

class vector_array_t
{
public:
	vector_array_t(arrType<double> angle_data);
	vector_t& operator[](const int& index);
	vector_t operator++(); 				//calculates the resultant vector 
							//of all the vectors in the array
	int Size();
	
private:	
	arrType<vector_t*> vector_array;

};

// *************** END DATA TYPES ********************

const double MAX_DISTANCE = 10.0; //centimeters
const double MAGNITUDES[3][6] = 
{
	{ 4.0, 25.0, 20.0, 28.0, 24.0,  2.0 }, //each row is a data set
	{ 7.0,  5.0,  4.0,  8.0, 28.0, 25.0 }, //each column corresponds to 
	{ 4.0,  5.0, 20.0, 28.0,  4.0, 12.0 }  //a sensor (column index 0 corresponds
			  	               //          to ir1, etc.)
};


arrType<double> initialAngles();


int main()
{
	vector_array_t ir(initialAngles());
	vector_t newDirection(0.0);

	for(int i = 0; i < 3; i++)
	{
		cout << "senory data: ";
		
		for(int j = 0; j < ir.Size(); j++)  //get sensory data
		{
			ir[j].magnitude = MAGNITUDES[i][j];
			cout << "ir" << j+1 << " = " << fixed << setprecision(2) << ir[j].magnitude << ", ";
		}
	
		newDirection = ++ir;

		cout << endl 
	             << "The robot should turn " << newDirection << endl << endl;
	}		

	return 0;
}

// ************************** general functions ************************************

arrType<double> initialAngles()
{
	arrType<double> angles;

	angles[0] = 45.0;
	angles = 30.0;
	angles = -30.0;
	angles = -45.0;
	angles = -130.0;
	angles = 130.0;
	
	return angles;
}
// ************************* end general functions *********************************


// ****************** DYNAMIC ARRAY SIZE DATA TYPE ********************************************

template <typename T>
//array intial size is one
//the array is not initialized
arrType<T>::arrType()
{
	intSize = 1;
	PtrArray = new T[1];
}

template <typename T>
//destructor
arrType<T>::~arrType()
{
	delete[] PtrArray;
}

template <typename T>
int arrType<T>::Size() //returns the size of the array
{return intSize;}

template <typename T>
//returns desired array index value
T& arrType<T>::operator[](const int& intRefINDEX)
{
	return PtrArray[intRefINDEX];
}

//***************************************************************************
//****************** Implementation instructions ****************************
//***************************************************************************
//This overloaded operator is used as an insert operator
//the array size will be increased by one
//all data in the array will be maintained and the new value will be added.
//example:
//arrType atArray;
  ////atArray.Size 1;
  ////atArray[0](value)
//atArray = 10;
  ////atArray.Size 2;
  ////atArray[0](value) ????	
  ////atArray[1](value) 10
  ////The array will insert a new index and stor the value 10 in it
template <typename T>
const T& arrType<T>::operator=(const T& RefINITIAL_VALUE)
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

// ****************** END DYNAMIC ARRAY SIZE DATA TYPE ********************************************

// *************************** VECTOR CLASS IMPLEMENATIONS *******************************************

ostream& operator<<(ostream& out, vector_t data)
{
	out << fixed << setprecision(2) << data.angle() << " degrees " << " with a magnitude of " << data.magnitude;

	return out;
}

		
vector_t::vector_t(double initAngle)	//default constructor
{
	ang = initAngle;
	rang = ang * M_PI / 180.0;

	magnitude = 0.0;
			
	cos_ang = cos(rang);
	sin_ang = sin(rang);
	tan_ang = tan(rang);	
}

vector_t vector_t::operator+(vector_t& rhs) //overloaded operators
{	
	
	if(rhs.magnitude > MAX_DISTANCE) 
		rhs.magnitude = 0.0;
	else
		rhs.magnitude = (MAX_DISTANCE - rhs.magnitude) / MAX_DISTANCE;

	double ax = this->magnitude * this->cos_ang;
	double bx = rhs.magnitude * rhs.cos_ang;
	double ay = this->magnitude * this->sin_ang;
	double by = rhs.magnitude * rhs.sin_ang;
	double cx = ax + bx;
	double cy = ay + by;
	double sqrcxcy = sqrt(cx*cx + cy*cy);
	double C = atan2( cy , cx ) *  180.0 / M_PI;
		
	vector_t temp(C);
	
	temp.magnitude = sqrcxcy;

	return temp;
}

const vector_t& vector_t::operator=(const vector_t& rhs)
{
	this->ang = rhs.ang;

	this->rang = rhs.rang;

	this->cos_ang = rhs.cos_ang;

	this->sin_ang = rhs.sin_ang;

	this->tan_ang = rhs.tan_ang;
		
	this->magnitude = rhs.magnitude;
	
	return rhs;
}
	
double vector_t::angle() 	   	//degrees
{ return ang; }

double vector_t::rangle()
{ return rang; }

double vector_t::cos_angle()
{ return cos_ang; }

double vector_t::sin_angle()
{ return sin_ang; }

double vector_t::tan_angle()
{ return tan_ang; }

// ********************************* END VECTOR CLASS ********************************************

// ********************************* VECTOR ARRAY CLASS *****************************************

// * the number of angles (in degrees) must correspond to the number of vectors
// * you wish to have in the array.  after the array is set up, the array size 
// * and the angles of the vectors are static; the magnitudes of each vector may 
// * be altered
// ***************************************************************************
vector_array_t::vector_array_t(arrType<double> angle_data)
{
	vector_array[0] = new vector_t(angle_data[0]);

	for(int i = 1; i < angle_data.Size(); i++)
		vector_array = new vector_t(angle_data[i]);

}

vector_t& vector_array_t::operator[](const int& index)
{ return *(vector_array[index]); }

vector_t vector_array_t::operator++()
{
	vector_t temp(0);
	temp.magnitude = 0.0;

	for(int i = 0; i < vector_array.Size(); ++i)
		temp = temp + *(vector_array[i]);

	int i = (temp.angle() > 0) ? -180 : 180;
	
	vector_t retVal(temp.angle() + i);
	retVal.magnitude = temp.magnitude;
	
	return retVal;
}

int vector_array_t::Size()
{ return vector_array.Size(); }

// ***************************** END VECTOR ARRAY CLASS ****************************************

