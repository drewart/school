// ----------------------------------------------------------------------------
// Project:		CS342 Lab1 
// File:		lab1.cpp
// Created By:	drpier
// Created Date: 3/30/2012
//
// Description:
//    Lab1 reads student data from file inserts that data into an array
//    Creates a Histogram and caclulates Average grade
//
//
// Assumptions: 
//   file ../data1.txt exist
//	 data1.txt line format ^\w+\s\w+\s\d+$
//   data1.txt contains lines
//   grades are numeric
//   any student with a grade outside grade boundaries is ignored
//   names are less than 30 char

#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int const MAXSIZE = 100;	    // maximum number of records in total
int const MAXLENGTH = 31;	    // maximum string length 
int const MAXGRADE = 100;           // highest possible grade
int const LOWGRADE = 0;             // lowest possible grade
int const HISTOGRAMSIZE = (MAXGRADE-LOWGRADE)/10 + 1;     // grouped in tens

// information of one student
struct StudentType  
{		    
	int grade;		    // the grade of the person
	char last[MAXLENGTH];	    // last name (MAXLENGTH-1 at most)
	char first[MAXLENGTH];	    // first name (MAXLENGTH-1 at most)
};

// prototypes go here
bool sortInput(ifstream&,StudentType[],int&);	//reads file, sorts into array
bool validStudentData(const StudentType&);				//validates grade range
void displayList(const StudentType[],const int);			//display student list
void setHistogram(int[],const StudentType[],const int);		// calc set histogram
void displayHistogram(const int[]);							// prints out histogram
int findAverage(const StudentType[],const int);				// calc average grade

//------------------------------- main ----------------------------------------
int main()  
{
   StudentType students[MAXSIZE];   // list of max of MAXSIZE number of students
   int size = 0;                    // total number of students
   int histogram[HISTOGRAMSIZE];    // grades grouped in tens
   int average = 0;                 // average exam score, truncated

   // creates file object and opens the data file
   ifstream infile("../data1.txt");
   if (!infile)  
   { 
      cout << "File could not be opened." << endl; 
      return 1;  
   }

   // read and sort input by last then first name
   bool successfulRead = sortInput(infile, students, size);              

   // display list, histogram, and class average 
   if (successfulRead) 
   {
	   displayList(students,size);
	   setHistogram(histogram,students,size);
	   displayHistogram(histogram);
	   average = findAverage(students,size);
	   cout << "Average grade: " << average << endl << endl;
   }
   else 
   {
	   cerr << "UnsuccessfulRead in sortInput" << endl;
	   return 1;
   }
   return 0;
}//end main

/****************************** FUNCTIONS *************************************/

/****************************** sortInput **************************************
* @Method: sortInput
* @Description: Reads from data file, validates data and insert sorts into array
*               set StudentType array, and size i.e. number of student grades.
*
* @Req: infile file exists
*/
bool sortInput(ifstream& infile,StudentType students[],int& size)
{
	   //temp Student
	   StudentType newStudent;
	   //read new student from file
	   while (size < MAXSIZE && infile >> newStudent.last
                                   >> newStudent.first
						>> newStudent.grade       
			 )
	   {
		   //make sure we have valid input
		   if (validStudentData(newStudent))
		   {
			   //set insert at end of array
			   int insertIndex=size;
			   //loop for insert point
			   for(int i=size-1;i>=0;i--)
			   {
				//compare last name and first name 
				// in array for insert index   
				   int lastCmp = strcmp(students[i].last
							,newStudent.last);
				   if (lastCmp > 0 || 
						(
						lastCmp == 0 && 
						strcmp(students[i].first
							,newStudent.first) > 0
						)
					  )
				   {
					    //shift student+1
						students[i+1] = students[i];
						//set insert point
						insertIndex=i;
				   }
				   else 
				   {
					//no students with greater last,first 
					// found insert point/index
					break;
				   }
			   }//end for
			   students[insertIndex] = newStudent;
			   size++;
		   }//end if validStudentData

	   }//end while
      

   return true;
}//end sortInput

/****************************** validStudentData ******************************
* @Method: validStudentData
* @Description: validates student grade 
* @Req: grade variable is set
*/
bool validStudentData(const StudentType& student)
{
	//grade needs to be between 0 .. 100
	if (student.grade >=LOWGRADE && student.grade <= MAXGRADE)
		return true;
	else
		return false;
}//end validStudentData

/****************************** displayList ***********************************
* @Method: displayList
* @Description: validates student grade 
* @Req: grade variable is set
*/
void displayList(const StudentType students[],const int size)
{
	cout << "List of names sorted:" << endl;
	for(int i=0;i<size;i++)
	{
		cout << setw(3) << students[i].grade << " "  
				<< students[i].last	<< " " 
				<< students[i].first << endl;
	}//end for
	cout << endl; //extra return
}//end displayList

/****************************** setHistogram **********************************
* @Method: setHistogram
* @Description: puts the student grades into Histogram array
* @Req: size is the number of students set in array
*/
void setHistogram(int histogram[],const StudentType students[],const int size)
{
	int i;
	//init histogram array to 0
	for(i=0;i<HISTOGRAMSIZE;i++)
		histogram[i] = 0;

	//for student grades put in histogram bucket
	for(i=0;i<size;i++)
	{
		//calc historam bucket
		int index = students[i].grade / 10 + 1;
		//add to histogram
		histogram[index-1]++;

	}//end for

}//end setHistogram

/****************************** displayHistogram *******************************
* @Method: displayHistogram
* @Description: displays histogram of size HISTOGRAMSIZE
* @Req: setHistogram called
*/
void displayHistogram(const int histogram[])
{
	//header
	cout << "Histogram of grades:" << endl;
	//print histogram range/groups
	for(int i=0;i<HISTOGRAMSIZE;i++)
	{
		//Histogram start range Note: 0 * 10 = 0
		
		cout << setw(3) << i * 10 << "--> ";

		//Histogram end 
		//  i+1 (next range) * 10 (group) -1 
		//  (subtract 1 to get end range)
		int endrange = ((i+1) * 10)-1;
	
		cout << setw(3);
		
		//Histogram edge case 100--> 100
		if ((endrange) > MAXGRADE)
			cout << MAXGRADE;
		else
			cout << endrange;
		
		cout << " ";
		
		//print out Histogram stars
		for(int x=0;x<histogram[i];x++)
			cout << "*";
		
		cout << endl;
	}//end for
	cout << endl;
}//end displayHistogram

/****************************** findAverage **********************************
* @Method: findAverage
* @Description: caclulates the grade total 
* 		then divides by size to return average
* @Req: size number of StudentType in array 
*/
int findAverage(const StudentType students[],const int size)
{
	int total=0;

	for(int i=0;i<size;i++)
		total += students[i].grade;

	return (total / size);
}//end findAverage
