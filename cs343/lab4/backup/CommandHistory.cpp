#include "CommandHistory.h"

char CommandHistory::Letter = 'H';

CommandHistory::CommandHistory()
{
  commandChar = 'H';
  commandName = "History";
}

CommandHistory::~CommandHistory()
{
  cout << "~CommandHistory()" << endl;
}

//--------------------------------------------------------------------------
//
//run
//
//
//
bool CommandHistory::run(Store* store)
{
  Customer* cust;
  if (store->getCustomer(customerId,cust))
  {
    cust->printHistory();
    return true;
  }
  else
    cout << "Unable to find customer with Id: " << customerId << endl; 
  
  return false;
}

//--------------------------------------------------------------------------
//
//setData
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
//write
//
//
//
void CommandHistory::write(ostream& out) const
{
   out << " CustomerID: "<< customerId <<  " history " << endl;
}//end write

//--------------------------------------------------------------------------
//
//createInstance
//
//
//
Command* CommandHistory::createInstance()
{
  return new CommandHistory();

}//end createInstance()


