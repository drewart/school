#include "CommandShowStore.h"

char CommandShowStore::Letter = 'S';

CommandShowStore::CommandShowStore()
{
   commandChar = 'S';
   commandName = "ShowStore";
}

CommandShowStore::~CommandShowStore()
{
  //cout << "~CommandShowStore()" << endl;
}

//--------------------------------------------------------------------------
//
//run
//
//
//
bool CommandShowStore::run(Store* store)
{
  cout << endl;
  store->displayStore();
  cout << endl;
  return true;
}

//--------------------------------------------------------------------------
//
//setData
//
//
//
bool CommandShowStore::setData(ifstream& stream)
{
  
  string s;
  getline(stream,s); //read eol
  //cout << "showstore '" << s << "'" << endl;
  return !stream.eof();
}//end setData

//--------------------------------------------------------------------------
//
//write
//
//
//
void CommandShowStore::write(ostream& out) const
{
  out << "Show Store" << endl;
}//end write

//--------------------------------------------------------------------------
//
//createInstance
//
//
//
Command* CommandShowStore::createInstance()
{
  return new CommandShowStore();

}//end createInstance()

