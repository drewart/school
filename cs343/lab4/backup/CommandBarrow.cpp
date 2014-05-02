#include "CommandBarrow.h"

char CommandBarrow::Letter = 'B';


CommandBarrow::CommandBarrow()
{
  commandChar = 'B';
  commandName = "Barrow";
  item = NULL;
}

//{{{CommandBarrow
/*CommandBarrow::CommandBarrow(CommandBarrow& cmd)
{

}//end CommandBarrow*/
//}}}

//{{{~CommandBarrow
CommandBarrow::~CommandBarrow()
{
  cout << "~CommandBarrow()" << endl;
  //clean up item
  if (item != NULL)
    delete item;
}
//}}}

//setData
bool CommandBarrow::setData(ifstream& stream)
{
   stream.ignore(1);
   stream >> customerId;
   stream.ignore(1);
   char media;
   stream >> media;
   stream.ignore(1);
   getline(stream,searchString);

   if (media != 'D')
   {
     error = "bad media type";
     return false;
   }
   
   return !stream.eof();
}//end setData

//run
bool CommandBarrow::run(Store* store)
{   
   bool commandResult = false;
  Customer* cust = NULL;
  if (store->getCustomer(customerId,cust))
  {
    Item *movie;
    if (store->findItem(this->searchString,movie))
    {
      if (movie->removeOneInventory())
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
        cout << "Unable find movie with: " << searchString << endl;
  }
  else
    cout << "Unable to find customer with Id: " << customerId << endl; 

  return commandResult;
}//end run


//virtual 
void CommandBarrow::write(ostream& out) const
{
  //write
  out << " CustomerID: "<< customerId << " " << commandName <<  " '" << this->searchString << "'" << endl;

}//end write

//createInstance
Command* CommandBarrow::createInstance()
{
  return new CommandBarrow();
}//end createInstance

/*ostream& operator<<(ostream& out, const CommandBarrow &cmd)
{
  cmd.write(out);
  return out;
}
*/

