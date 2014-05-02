#include "CommandBarrow.h"

char CommandBarrow::Letter = 'B';

//------------------------------------------------------------------------------
// <Function> 
// <description>
//
//

CommandBarrow::CommandBarrow()
{
  commandChar = 'B';
  commandName = "Barrow";
  item = NULL;
}

//{{{~CommandBarrow
//------------------------------------------------------------------------------
// CommandBarrow 
//
//
//
CommandBarrow::~CommandBarrow()
{
  //cout << "~CommandBarrow()" << endl;
  //clean up item
  item = NULL;
}
//}}}

//------------------------------------------------------------------------------
// <Function> 
// <description>
//
//
bool CommandBarrow::setData(ifstream& stream)
{
   
   stream.ignore(1);       // ignore space
   stream >> customerId;   //read id
   stream.ignore(1);       // ignore space
   
   char media;
   stream >> media;
   stream.ignore(1);
   
   //read rest of line as searhString
   getline(stream,searchString);

   //validate media type D for DVD if not return fail
   if (media != 'D')
   {
     error = "bad media type";
     return false;
   }
   
   return !stream.eof();
}//end setData

//------------------------------------------------------------------------------
// run(Store* store) 
//   preforms a barrow command on the store
//
//

bool CommandBarrow::run(Store* store)
{   
  bool commandResult = false;    //did it work
   
  Customer* cust = NULL;
  
  //get customer for barrow
  if (store->getCustomer(customerId,cust))
  {
    //find movie
    Item *movie;
    if (store->findItem(this->searchString,movie))
    {
      //found movie set local pointer
      this->item = movie;
      if (movie->removeOneInventory())
      {
        //add customer history
        cust->addHistory(this);
        // it worked
        commandResult = true;
      }
      else
      {
          //out of items
          cout << "Unable to " << commandName << "  ";
          item->writeBasic(cout);
          cout << endl;
      }
    }
    else 
        cout << "Unable find movie with: " << searchString << endl;
  }
  else
    cout << "Unable to find customer with Id: " << customerId << endl; 

  return commandResult;
}//end run


//------------------------------------------------------------------------------
// write 
// write the out put of the command
//
//

void CommandBarrow::write(ostream& out) const
{
  //write
  out << "DVD  " << commandName << "   ";
  item->writeBasic(out);
  out << endl;

}//end write

//------------------------------------------------------------------------------
// createInstance 
// creates a instance of the class
//
//
Command* CommandBarrow::createInstance()
{
  return new CommandBarrow();
}//end createInstance



