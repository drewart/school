#ifndef MOVIECLASSIC_H
#define MOVIECLASSIC_H

#include "Movie.h"



class MovieClassic : public Movie 
{

public:
   
  MovieClassic();
  virtual ~MovieClassic();

  virtual void write(ostream&) const;
  virtual bool setData(ifstream&);
  
  virtual bool valid();

  //compare operators
  /*virtual int compareTo(MovieClassic*) const;

  virtual bool operator<(const MovieClassic&) const ;  
  virtual bool operator>(const MovieClassic&) const;   
  */
  virtual bool operator==(const MovieClassic&) const;

  virtual Movie* createInstance();
  
  static const char Letter;
  
private:

  int month;
  
  string actor;

};

#endif



