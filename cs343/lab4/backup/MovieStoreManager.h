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


/// MovieStoreManager manages the movie store object, process commands on store object
/// 
///
class MovieStoreManager
{

public:
  MovieStoreManager();       //construct store manager
  ~MovieStoreManager();     // destroy store manager
 
  void loadMovies( ifstream& );

  void loadCommands( ifstream& );

  void loadCustomers( ifstream& );

  void Run();

private:
  Store* store;
  CommandQueue commandQueue;
  
  //CommandFactory commandFactory;

};


#endif

