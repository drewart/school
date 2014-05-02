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
  //cout << "~CommandQueue()" << endl;
  //clean up item
  //if (item != NULL)
  //  delete item;
  item = NULL;
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
      //tie found for ref
      this->item = movie;
      if (movie->addOneInventory())
      {
        cust->addHistory(this);
        commandResult = true;
      }
      else
      {
          cout << "Unable to " << commandName << "  ";
          item->writeBasic(cout);
          cout << endl;
      
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
  //write
  out << "DVD  " << commandName << "   ";
  item->writeBasic(out);
  out << endl;

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

