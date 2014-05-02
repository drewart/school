#include "CommandHistory.h"

char CommandHistory::Letter = 'H';

CommandHistory::CommandHistory()
{
  commandChar = 'H';
  commandName = "History";
}

CommandHistory::~CommandHistory()
{
  //cout << "~CommandHistory()" << endl;
}

//--------------------------------------------------------------------------
//
// run
// runs command
//
//
bool CommandHistory::run(Store* store)
{
  Customer* cust;
  if (store->getCustomer(customerId,cust))
  {
    cout << endl;
    cout << "   *** Customer ID = " << customerId <<  "  " << cust->getName() << "*** " << endl;
    cust->printHistory();
    cout << endl << endl;
    return true;
  }
  else
    cout << "Unable to find customer with Id: " << customerId << endl; 
  
  return false;
}

//--------------------------------------------------------------------------
//
// setData
// set data for the command
//
//
//
bool CommandHistory::setData(ifstream& stream)
{
  stream >> customerId;
  string s;
  getline(stream,s); //read eol
  //cout << "history '" << s << "'" << endl;
  return !stream.eof();
}//end setData

//--------------------------------------------------------------------------
//
// write command object
//
//
//
void CommandHistory::write(ostream& out) const
{
   out << " CustomerID: "<< customerId <<  " history " << endl;
}//end write

//--------------------------------------------------------------------------
//
// createInstance
// create CommandHistory instance as Command*
//
//
Command* CommandHistory::createInstance()
{
  return new CommandHistory();

}//end createInstance()


