// *********************************** IntSet ***********************************
// Project:		CS342 Lab2 
// File:		intset.h
// Created By:	drpier
// Created Date: 4/7/2012
//
//
//
//---------------------------------------------------------------------------

#ifndef INTSET_H
#define INTSET_H
#include <iostream>
using namespace std;


//default int set bool array
const int INTSET_INIT_SIZE=100;

//max set number
const int INTSET_MAX_SIZE=25000;

/*****************************************************************************
*
* Lab2 IntSet a class ADT that performs a union, diff and interset on int sets
*
* Assumptions: 
*    Five parameters into the constructor
*    number in set less than INTSET_MAX_SIZE i.e. 25000
*	 No const int as params
*	 unhandled new returning NULL (out of project scope)
*    >> at least one number entered
*	 << no return, ints all on one line, no endl
*
************/		
class IntSet 
{
	// overloaded <<:  
	//    prints int set
	friend ostream& operator<<(ostream&, const IntSet&);

	// overloaded >>: 
	//    reads line of ints into IntSet
	friend istream& operator>>(istream&, IntSet&);
	
public:
	//default Constructor Note: -1 used like NULL if not set
	IntSet(int=-1,int=-1,int=-1,int=-1,int=-1);		//5 param Constructor 
	IntSet(const IntSet&);							//Copy Constructor 
	~IntSet();										//Destructor

	bool insert(int);								//add to int set
	bool remove(int);								//removes int from int set

	bool isEmpty(void) const;						//return true if empty set
	bool isInSet(int) const;						//return true if int in set

   // set operators
   IntSet operator+(const IntSet &) const;			// union IntSet
   IntSet operator-(const IntSet &) const;			// difference of two sets
   IntSet operator*(const IntSet &) const;			// the intersection of two sets
   
   
   bool operator==(const IntSet &) const;			// is object == parameter?
   bool operator!=(const IntSet &) const;			// is object != parameter?

   // assignment operators
   IntSet& operator+=(const IntSet &);				// current object += parameter
   IntSet& operator-=(const IntSet &);				// current object -= parameter
   IntSet& operator*=(const IntSet &);				// current object *= parameter
   IntSet& operator=(const IntSet &);				// current object =  parameter
    
   // public count of numbers
   int count;
   
private:
	
	bool growCheck(int);							// bool array grow check 
	
	//max number used to limit for loop
	int maxNumber;
	
	//pointer to bool array
	bool *ptrSet;
	
	//ptrSet array size
	int size;

};

#endif
