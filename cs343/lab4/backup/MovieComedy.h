#ifndef MOVIECOMEDY_H
#define MOVIECOMEDY_H

#include "Movie.h"

using namespace std;

class MovieComedy : public Movie 
{

public:
  MovieComedy();
  virtual ~MovieComedy();

  virtual void write(ostream&) const;
  virtual bool setData(ifstream&);
  
  //virtual int compareTo(Item*) const;

  //virtual int compareTo(Movie*) const;
  //compare operators 
  /*virtual int compareTo(const Movie&) const;
  virtual int compareTo(const MovieComedy&) const;
  
  virtual bool operator<(const MovieComedy&) const;  
  virtual bool operator>(const MovieComedy&) const;   
  virtual bool operator==(const MovieComedy&) const;
  */

  virtual Movie* createInstance();

  static const char Letter;
  
private:

};

#endif


