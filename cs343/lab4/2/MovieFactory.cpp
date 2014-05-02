#include "MovieFactory.h"

#include "MovieClassic.h"
#include "MovieComedy.h"
#include "MovieDrama.h"



//private factory instance created
bool MovieFactory::instanceCreated = false;

//private singleton instance of factory
MovieFactory* MovieFactory::factory=NULL;
//int CommandFactory::commandCount = 0;


//{{{MovieFactory
MovieFactory::MovieFactory()
{
  //firstCommand = lastCommand = NULL;
  firstMovie = lastMovie = NULL;
  movieCount=0;
  
  for(int i = 0; i < MOVIE_FACTORY_HASH_SIZE; i++)
  {
    movieObjects[i] = NULL;
  }
  movieObjects[MovieClassic::Letter - 'A'] = new MovieClassic();
  movieObjects[MovieDrama::Letter   - 'A'] = new MovieDrama();
  movieObjects[MovieComedy::Letter  - 'A'] = new MovieComedy();
  
  
}
//}}}


//{{{~CommandFactory
//------------------------------------------------------------------------------
//
// ~CommandFactory
//  clean up commands
//
MovieFactory::~MovieFactory()
{
  //cout << "~MovieFactory()" << endl;
  MovieNode* temp;
  MovieNode* current = firstMovie;
  while(current != NULL)
  { 
    temp = current;
    current = current->next;
    delete temp->movie; //clean up command
    delete temp; //clean up CommandNode
  }   

  for(int i = 0; i < MOVIE_FACTORY_HASH_SIZE; i++)
  {
    if (movieObjects[i] != NULL)
      delete movieObjects[i];
  }
}
//}}}

//{{{getInstance()
//private internal Singleton getInstance()
MovieFactory* MovieFactory::getInstance()
{
  if (!instanceCreated)
  {
    factory=new MovieFactory();
    instanceCreated = true;
    return factory;
  }
  else
  {
    return factory;
  }
}
//}}}

void MovieFactory::cleanUp()
{
  if (instanceCreated)
  {
    instanceCreated = false;
    delete factory;
    factory = NULL;
  }
}


//{{{createCommand
Movie* MovieFactory::createMovie(char ch)
{
  return getInstance()->createMovieImpl(ch);
}
//}}}


Movie* MovieFactory::createMovieImpl(char ch)
{
 
  Movie* movie=NULL;
  
  int subscript = hash(ch);
  
  //handle edge cases
  if (subscript < 0 || subscript > 25)
    return movie;

   if (movieObjects[subscript] != NULL)
   {
     movie = movieObjects[subscript]->createInstance();
     if (movie != NULL)
     {
       movieCount++;
       addMovie(movie);
     }
   }

   return movie;
}


int MovieFactory::hash(char ch)
{
    return ch-'A';
}

//{{{addMovie
void MovieFactory::addMovie(Movie* movie)
{
  MovieNode *node = new MovieNode();
  node->movie = movie;
  node->count = 20;
  node->next = NULL;

  if (firstMovie == NULL)
  {
    firstMovie = lastMovie = node;
  } 
  else
  {
    lastMovie->next = node;
    lastMovie = node;
  
  }
}//end addMovie
//}}}

