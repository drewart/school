#include "Movie.h"

struct MovieNode 
{
  Movie* movie;
  int count;
  MovieNode* next;
};


const int MOVIE_FACTORY_HASH_SIZE = 26;

class MovieFactory
{
  
public:
  static Movie* createMovie(char c);
  static int getInventory(Movie*);
  static MovieFactory* getInstance();
  static void cleanUp();

private:
   MovieFactory();
  ~MovieFactory();
  

  Movie* createMovieImpl(char c);
   
  int hash(char c);
    
  static bool instanceCreated;
  static MovieFactory *factory;
  
  void addMovie(Movie*);

  Movie* movieObjects[MOVIE_FACTORY_HASH_SIZE];
  
  

  MovieNode* firstMovie;
  MovieNode* lastMovie;
  int movieCount;


};

