//**********************************************************************************
#ifndef MOVIESTORE_H
#define MOVIESTORE_H

#include <string>
#include "Store.h"
#include "ItemTree.h"
#include "Movie.h"

using namespace std;

class MovieStore : public Store
{
  
public: 
  MovieStore(string);
  ~MovieStore();

  virtual bool addItem(Item*);

  virtual bool findItem(string,Item*&);

  virtual void displayStore() const;

  virtual void displayCustomerHistory(int i) const;

  virtual bool checkoutItem(Item*);

  virtual bool returnItem(Item*);


private:
  ItemTree movieTree;      //movie tree  
  //movies with Customer
  //MovieHash* movieHash;      //movie hash 

};


#endif

