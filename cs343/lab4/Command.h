#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
//#include <iomanip>
#include <fstream>
#include <string>
#include "Store.h"

using namespace std;

//------------------------------------------------------------------------------
//
// Command
// Base Parent abstract class for running commands on the store
//
//
//
class Store;
class Command 
{
	
friend ostream& operator<< (ostream&, const Command &);



public:
  Command(); 
  virtual ~Command(); 
  
  //virtual funtions to implement
	virtual bool run(Store*) = 0;
	virtual bool setData(ifstream&) = 0;                	//sets data from file
	virtual void write(ostream&) const = 0;
	
	virtual Command* createInstance() = 0;
  
	//name of the command
   string getCommandName() const;
 
  //return customer Id
  int getCustomerId() const;
  
  // returns the error if there is a data problem
  string getError()
  {
    return error;
  }

protected:
  char commandChar;        //char of the command
  
  string commandName;      //command name      
  
  int customerId;          //not alwayed needed
  
  string searchString;     //movie search string

  string error;         //stores error with data

  //static count of all commands
  static int cmdCount;     

};

#endif

