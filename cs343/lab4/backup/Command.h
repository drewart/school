#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
//#include <iomanip>
#include <fstream>
#include <string>
#include "Store.h"

using namespace std;

class Store;
class Command 
{
	
friend ostream& operator<< (ostream&, const Command &);



public:
  Command(); 
  virtual ~Command(); 
  
	virtual bool run(Store*) = 0;
	virtual bool setData(ifstream&) = 0;                	//sets data from file
	virtual void write(ostream&) const = 0;   	
	virtual Command* createInstance() = 0;
  
  string getCommandName() const;
 
  int getCustomerId() const;
  

  string getError()
  {
    return error;
  }

protected:
  char commandChar;
  string commandName;
  int customerId;
  string searchString;

  string error;

  static int cmdCount;

};


//-----------------------------------------------------------------------------
//
//
//
//
/*ostream& operator<< (ostream& out, const Command &cmd)
{
  cmd.write(out);
  return out;
}
*/



#endif

