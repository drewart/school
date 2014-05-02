#include "Movie.h"

struct MovieNode 
{
  Movie* movie;
  int count;
  MovieNode* next;
};


class MovieHashFactory
{
  
public:
  static Movie* createMovie(char c);
  static int getInventory(Movie*);
  static MovieHashFactory* getInstance();

private:
   MovieHashFactory();
  ~MovieHashFactory();
  

  Movie* createMovieImpl(char c);
   
  int hash(char c);
    
  static bool instanceCreated;
  static MovieHashFactory *factory;
  
  void addMovie(Movie*);

  Movie* movieObjects[26];
  
  

  MovieNode* firstMovie;
  MovieNode* lastMovie;
  int movieCount;


};
