// *********************************** IntSet ***********************************
// Project:		CS342 Lab2 
// File:		intset.cpp
// Created By:	drpier
// Created Date: 4/7/2012
//
// Description:
//    Lab2 IntSet class to learn custom operators
//    
//
//

#include "intset.h"


/*********************************** IntSet ***********************************
* Description:Constructor with 5 parameters
*
* @Req: int >= 0
*******/
IntSet::IntSet(int a,int b,int c, int d,int e)
{
	count=0;		//start with 0 count

	//allocate bool memory
	ptrSet = new bool[INTSET_INIT_SIZE+1];

	//set init bool = false
	for(int i = 0; i <= INTSET_INIT_SIZE; i++)
		ptrSet[i] = false;						//all false

	// -1 for case new IntSet(0)
	maxNumber = -1;		
	
	//init size
	size = INTSET_INIT_SIZE;

	//insert params Note: ignoring bool return
	insert(a);
	insert(b);
	insert(c);
	insert(d);
	insert(e);
	
}//end IntSet

/*********************************** IntSet ***********************************
* Description: Copy Constructor
*
* 
*******/
IntSet::IntSet(const IntSet& orig)
{
	ptrSet = new bool[orig.size+1];
	
	for(int i=0;i<=orig.size;i++)
	{
		ptrSet[i] = orig.ptrSet[i];;
	}//end for
	
	maxNumber = orig.maxNumber;
	size = orig.size;
	count = orig.count;

}//end IntSet copy

/*********************************** ~IntSet ***********************************
* Description: Descructor
*
* 
*******/
IntSet::~IntSet()
{
	//de-allocate memory
	delete []ptrSet;
	ptrSet = NULL;
}//end ~IntSet()

/*********************************** isEmpty ***********************************
* Description: returns if the set is empty or count == 0
*
* 
*******/
bool IntSet::isEmpty(void) const
{
	return ( count == 0 );
}//end isEmpty

/*********************************** isInSet ***********************************
* Description: returns true if the int is in the set
*
* @Req: int > 0 
*******/
bool IntSet::isInSet(int n) const
{
	if (n > maxNumber || n < 0)
		return false;
	else
		return ( ptrSet[n] );
}//end isInSet


/*********************************** operator+ ***********************************
* Description: returns  union of two IntSet
*
* 
*******/
IntSet IntSet::operator+(const IntSet& set) const
{
	IntSet temp;
	

	int max = (maxNumber >= set.maxNumber) ? maxNumber : set.maxNumber;

	for(int i = 0; i <= max; i++)
	{	
		if (isInSet(i) || set.isInSet(i))  //if has either insert
			temp.insert(i);
	}//end for
	
	return temp;
}//end +

/*********************************** operator- ***********************************
* Description: difference of two sets
*
* 
*******/
IntSet IntSet::operator-(const IntSet& set) const
{
	IntSet temp = *this;

	for(int i = 0; i <= set.maxNumber; i++)
	{
		if (temp.isInSet(i) && set.isInSet(i))
			temp.remove(i);
	}
	return temp;
}//end -

/*********************************** operator* ***********************************
* Description: returns intersetion of two sets
*
* 
*******/
IntSet IntSet::operator*(const IntSet& set) const
{
	
	IntSet temp;
	
	//getting lowest maxNumber of sets for common
	int minMax = (set.maxNumber < maxNumber) ? set.maxNumber : maxNumber;

	//loop and add common numbers to insert into new set
	for(int i = 0; i <= minMax; i++)
	{
		if (isInSet(i) && set.isInSet(i))
			temp.insert(i);
	}
	return temp;
}//end *


/*********************************** operator-= ***********************************
* Description: set the intersection a IntSet to this IntSet
*
* 
*******/
IntSet& IntSet::operator*=(const IntSet& set)
{
	//loop removing non common ints in set
	//NOTE: not removing == 
	for(int i=0;i<=maxNumber;i++)
	{
		if (i > set.maxNumber && isInSet(i))
			remove(i);
		else if (isInSet(i) != set.isInSet(i))	
			remove(i);
	}
	return *this;
}//end *=

/*********************************** operator-= ***********************************
* Description: union a IntSet to this IntSet
*
* 
*******/
IntSet& IntSet::operator+=(const IntSet& set)
{
	//
	for(int i = 0; i <= set.maxNumber; i++)
	{
		if (set.isInSet(i))
			insert(i);			//NOTE: insert ignore if already set
	}//end for

	return *this;
}//end +=

/*********************************** operator-= ***********************************
* Description: subtracts set from this IntSet
*
* 
*******/
IntSet& IntSet::operator-=(const IntSet& set)
{
	//loop removing set int from this
	for(int i = 0; i <= maxNumber; i++)
	{
		if (i > set.maxNumber) 
			break;
		else if (isInSet(i) == set.isInSet(i))
			remove(i);
	}
	return *this;
}//end -=



/*********************************** operator= ***********************************
* Description: assignment sets IntSet to parameter set 
*
* 
*******/
IntSet& IntSet::operator=(const IntSet& set)
{
	//A = A check
	if (this == &set)
		return *this;					//if A == A return left A

	//init temp array
	bool *ptr = new bool[set.size+1];
	delete [] ptrSet;					//remove current set
	ptrSet = ptr;						//set new bool array

	//copy set array
	for(int i = 0; i <= set.size; i++)
	{
		ptrSet[i] = set.ptrSet[i];
	}
	
	//copy members
	maxNumber = set.maxNumber;
	size = set.size;
	count = set.count;

	return *this;
}//end =

/*********************************** operator= ***********************************
* Description: returns true if parameter IntSet == this IntSet
*
* 
*******/
bool IntSet::operator==(const IntSet& set) const
{
	//init check if count same && maxNumber == 
	//then check if each int in set matches
	if (count == set.count && maxNumber == set.maxNumber)
	{
		for(int i = 0; i <= maxNumber; i++)
		{
			if (ptrSet[i] != set.ptrSet[i])
				return false;
		}
		//unable to find mismatch so *this==set
		return true;
			
	}
	else
		return false;
}//end ==

/*********************************** operator= ***********************************
* Description: returns true if parameter IntSet != this IntSet
*
* 
*******/
bool IntSet::operator!=(const IntSet& set) const
{
	//assume == and check where sets do not match
	if (count == set.count && maxNumber == set.maxNumber)
	{
		for(int i = 0; i <= maxNumber; i++)
		{
			if (ptrSet[i] != set.ptrSet[i])
				return true;
		}
		return false;
	}
	else
		return true;
}//end !=

/******************** insert ***********************************************
* Description: returns true if int was able to be inserted into array 
*              or was in array
*
****************************/
bool IntSet::insert(int n)
{
	
	//range & size check
	if (n >= 0 && n <= INTSET_MAX_SIZE && growCheck(n))
	{
		if (!ptrSet[n]) count++;	//don't count duplicate

		ptrSet[n] = true;

		//set max number
		maxNumber = (n > maxNumber) ? n : maxNumber;
		
		return true; //was able to insert
	}
	else
		return false;
}//end insert

/******************** remove ***********************************************
* Description: removes a int from IntSet if it exists
*
*
****************************/
bool IntSet::remove(int n)
{
	//range check
//	if (n > size && n < 0)
	if (n > size || n < 0 || n > maxNumber)
	{
		return false;
	}
	else if (ptrSet[n])
	{
		ptrSet[n] = false;
		count--;				//track Set count
		if (n == maxNumber)
		{
			for(int i=maxNumber;i>=0;i--)
			{
				if (ptrSet[i]) {

					maxNumber=i;
					break;
				}				
			}
		}		
		if (count == 0)
			maxNumber = -1;
		return true;			//was able to remove int
	}
	else
		return false;
}//end remove


/******************** growCheck ***********************************************
* Description: returns true if int is in size current size limit or able to grow array
*				returns false if unable to grow array		
*
*
****************************/
bool IntSet::growCheck(int n)
{
	if (n >= 0 && n <= size)
	{
		return true;
	}
	else if (n > size && n <= INTSET_MAX_SIZE)
	{
		bool* temp = new bool[n+1];
		
		for(int i = 0; i <= n; i++)
		{
			if (i <= maxNumber && ptrSet[i])
			{
				temp[i] = true;
			}
			else 
				temp[i] = false;
			
		}
		temp[n] = false;
		delete []ptrSet;

		ptrSet = temp;
		//update size
		size = n;
		return true;
	}
	else
		return false;
}//end growCheck


/******************** << ***********************************************
* Description: returns ostream of set output
*
* format { #} with spaces before #
****************************/
ostream& operator<<(ostream& out, const IntSet& set)
{
	out << '{';
	for(int i = 0; i <= set.maxNumber; i++)
		if (set.ptrSet[i])
			out << ' ' << i;
	out << '}';
	return out;
}//end <<

/******************** >> ***********************************************
* Description: reads input stream for int
*
* 
****************************/
istream& operator>>(istream& input, IntSet& intset)
{
	int num;
	
	do
	{
		input >> num;		//read int
		
		if (num < 0 || num > INTSET_MAX_SIZE)	//range check
			break;
		else 
			intset.insert(num);					//insert

	} while(input.peek() != '\n');				//end while stop read on enter/return 

   return input;								// e.g., enables cin >> x >> y;
}//end >>
