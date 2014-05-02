#define DEBUG
#include <string>
#include <iostream>
#include <fstream>



#include "MovieStoreManager.h"

using namespace std;

int main() 
{

    ifstream customerFile("data4customers.txt");
    if (!customerFile) 
    {
   	 cout << "File could not open data4customers.txt." << endl;
   	 return 1;
    }

    ifstream commandFile("data4commands.txt");
    if (!commandFile) 
    {
   	 cout << "File could not open data4commands.txt." << endl;
   	 return 1;
    }

    ifstream movieDataFile("data4movies.txt");
    if (!movieDataFile) 
    {
   	 cout << "File could not be data4movies." << endl;
   	 return 1;
    }

    MovieStoreManager movieStoreManager;

    //load customer
    movieStoreManager.loadCustomers(customerFile);
    
    //load movies
    movieStoreManager.loadMovies(movieDataFile);
    
    //load commands
    movieStoreManager.loadCommands(commandFile);
    
    //run the store commands
    movieStoreManager.Run();

    return 0;
}

