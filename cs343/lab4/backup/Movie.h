#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

#include "Item.h"


const int MAX_TITLE_DISPLAY_WIDTH = 20;
const int MAX_DIRECTOR_DISPLAY_WIDTH = 15;

const int DEFAULT_MOVIE_INVENTORY = 10;

class Movie : public Item 
{

public:
  Movie();
  virtual ~Movie();


  virtual bool setData(ifstream&);

  virtual bool valid();


  virtual void write(ostream&) const;
   
  //compare operators
  virtual int compareTo(Movie*) const;


  //virtual bool operator<(const Movie&) const;
  //virtual bool operator>(const Movie&) const;
  virtual bool operator==(const Movie&) const;

  virtual Movie* createInstance();

protected:
  string media;		//Description of Media Type ex. "DVD" or "BLU-RAY"
  char movieType;

  // director of the movie
  string director;


  // year of the movie
  int year;

  // month of the movie 0 if no month for DVD

       
};

#endif

