
#include "MovieStoreManager.h"


//{{{
MovieStoreManager::MovieStoreManager()
{
    store = new MovieStore("MOVIE");
}
//}}}

//{{{MovieStoreManager
MovieStoreManager::~MovieStoreManager()
{
  cout << "~MovieStoreManager()" << endl;
  //cleanup commands
  MovieFactory::cleanUp();
  CommandFactory::cleanUp();
  delete store;
}

//}}}


//{{{loadCustomers
void MovieStoreManager::loadCustomers(ifstream& stream)
{
  Customer* cust;
  do
  {
    cust  = new Customer();

    if (cust->setData(stream))
    {
      if (!store->addCustomer(cust))
      {
        cout << "Error Unable to add customer: " << cust << endl;
        delete cust;
      }
    }
    else
    {
      delete cust;
    }
  
  } while(!stream.eof());
}
//}}}

void MovieStoreManager::loadMovies(ifstream& stream)
{
  Item* movie;
  do 
  {
    char movieType;
    movieType  = stream.peek();
    movie = MovieFactory::createMovie(movieType);

    if (movie == NULL) 
    {
      string badLine;
      getline(stream,badLine);  //eat bad line
      if (stream.eof())
        break;
      
      if (badLine.length() > 0)
      {
        cout << "Movie Create Failure for line: " << endl;
        cout << " '" << badLine << "'" << endl << endl;
      }
      continue;
    }

    if (movie->setData(stream))
    {
      //yes this is bad hard coding, I would have inventory in a database
      if (movie->getTitle() == "Holiday")
      {
        movie->setInventory(20);
      }
      //add movie to store

      if (!store->addItem(movie))
      {
        cout << "Unable to add: " << *movie << endl;

      }
      //!added then delete
    }
    else if (movie->getError().length() > 0)
      cout << "Bad Movie Data: " << movie->getError() << endl;

  } while(!stream.eof());
  
}

void MovieStoreManager::loadCommands(ifstream& stream)
{
  
  char cmdChar;
  Command *cmd=NULL;
  do 
  {
     
    //read command char
    stream >> cmdChar;

    //create command from letter
    cmd = CommandFactory::createCommand(cmdChar);
    
    if (cmd != NULL)
    {
      if (cmd->setData(stream))
      {
        commandQueue.enqueue(cmd);
      }
      else
      {
        if (stream.eof())
          break;
        if (cmd->getError().length() > 0)
          cout << "Created Command Data Error: " << cmd->getError() << endl << endl;
      }
    }
    else
    {
      string nil;
      getline(stream,nil);

      cout << "Command Create Error for Line: "  << cmdChar << " " << nil << endl;
    }

  } while(!stream.eof());
  
}

void MovieStoreManager::Run()
{

  //run commands
  //cout << store << endl;
  Command* cmd;
  while(commandQueue.dequeue(cmd))
  {
    if (cmd->run(store))
    {
      store->history.add(cmd);
    }
  }
}

