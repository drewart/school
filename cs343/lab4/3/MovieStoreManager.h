//**********************************************************************************
#ifndef MOVIESTOREMANAGER_H
#define MOVIESTOREMANAGER_H 

//#include "Queue.h"
//#include "Command.h"
#include "Customer.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include "CommandQueue.h"
#include "CommandFactory.h"
#include "MovieFactory.h"
#include "Command.h"
#include "Movie.h"
#include "MovieStore.h"
#include "CustomerHashTable.h"

using namespace std;


//----------------------------------------------------------------------------
// class MovieStoreManager 
//
// MovieStoreManager manages the movie store object, process commands on store object
//
//  Example:
//   MovieStoreManager storeMgr;
//   //
//   storeMgr.loadXXX(ifstream);
//   ...
//   storeMgr.Run();
//  
// Assumptions:
//    -- speed and comlexity is not a major piece
//    -- upper and lower bounds test with sample data
//    -- 
//----------------------------------------------------------------------------

class MovieStoreManager
{

public:
  MovieStoreManager();       //construct store manager
  ~MovieStoreManager();     // destroy store manager
 
  //loads movies
  void loadMovies( ifstream& );

  //loads commands
  void loadCommands( ifstream& );

  //loads customers
  void loadCustomers( ifstream& );

  //runs queue of commands
  void Run();

private:
  //store instance of MovieStore as Store object
  Store* store;
  //queue for commands
  CommandQueue commandQueue;
  
  //CommandFactory commandFactory;

};


#endif

