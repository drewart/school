#ifndef STORE_H
#define STORE_H

#include <string>
#include "Item.h"
#include "Customer.h"
#include "Command.h"
#include "CustomerHashTable.h"
//#include "customer_tree.h"

using namespace std;

class Store 
{

public:
  //Store(string);
	virtual ~Store();

  virtual bool addItem(Item*)=0;     //abstract
	virtual bool addCustomer(Customer*);
  virtual bool getCustomer(int,Customer*&);
  
	//bool processCommand(Command&);   // processes queue
  virtual bool findItem(string,Item*&)=0;

  virtual bool checkoutItem(Item*)=0;

  virtual bool returnItem(Item*)=0;
  
  virtual void displayStore() const=0;

  //public list of history
  CommandList history;                  // stores history
protected:
	//CustomerHash* customer;            // pointer to BSTree object
	
	CustomerHashTable customerHash;
  string name;                       //name of the store

};

#endif

