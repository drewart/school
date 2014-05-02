#ifndef MOVIEDRAMA_H
#define MOVIEDRAMA_H

#include "Movie.h"



class MovieDrama : public Movie 
{

public:
  MovieDrama();
  virtual ~MovieDrama();

  //virtual void write(ostream&) const;
  virtual bool setData(ifstream&);
  
  //compare operators
  //virtual int compareTo(Movie*) const;
  //virtual int compareTo(const MovieDrama&) const;

  /*virtual bool operator<(const MovieDrama&) const;  
  virtual bool operator>(const MovieDrama&) const;   
  virtual bool operator==(const MovieDrama&) const;
  */
  virtual Movie* createInstance();

  static const char Letter;
  
private:

};

#endif


