#include "CommandReturn.h"


char CommandReturn::Letter = 'R';
//--------------------------------------------------------------------------
//
//CommandReturn
//
//
//
CommandReturn::CommandReturn()
{
  commandChar = 'R';
  commandName = "Return";
  item = NULL;
}

CommandReturn::~CommandReturn()
{
  cout << "~CommandReturn()" << endl;
  //clean up item
  if (item != NULL)
    delete item;
}

//--------------------------------------------------------------------------
//
//run
//
//
//
bool CommandReturn::run(Store* store)
{
  bool commandResult = false;
  Customer* cust = NULL;
  if (store->getCustomer(customerId,cust))
  {
    Item *movie;
    if (store->findItem(this->searchString,movie))
    {
      if (movie->addOneInventory())
      {
        cust->addHistory(this);
        commandResult = true;
      }
      else
      {
        cout << "Unable to " << commandName << searchString << endl;
      
      }
    }
    else
    {
        cout << "Unable find movie with: " << searchString << endl;
    }
  }
  else
    cout << "Unable to find customer with Id: " << customerId << endl; 
  return commandResult;
}

//--------------------------------------------------------------------------
//
//setData
//
//
//
bool CommandReturn::setData(ifstream& stream)
{
   stream.ignore(1);
   stream >> customerId;
   stream.ignore(1);
   char media;
   stream >> media;
   if (media != 'D')
   {
     error = "bad media type";
     return false;
   }
   stream.ignore(1);
   getline(stream,searchString);
   
   return !stream.eof();
}//end setData

//--------------------------------------------------------------------------
//
//write
//
//
//
void CommandReturn::write(ostream& out) const
{
  out << " CustomerID: "<< customerId << " " << commandName <<  " '" << this->searchString << "'" << endl;;
}//end write

//--------------------------------------------------------------------------
//
//createInstance
//
//
//
Command* CommandReturn::createInstance()
{
  return new CommandReturn();

}//end createInstance()

