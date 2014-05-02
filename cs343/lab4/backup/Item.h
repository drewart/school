//product.h
#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <fstream>
#include <string>


using namespace std;

class Item
{

  	friend ostream& operator<< (ostream&, const Item &);

public:
  Item();
  ~Item();

  int getId() const;
  void setId(int);

  string getSku() const;
  void setSku(string);

  string getTitle() const;

  string getError() const;

  string getSortString();

  virtual void write(ostream&) const;

  virtual bool setData(ifstream&);

  virtual bool valid();

  virtual int compareTo(Item*) const;
  
  virtual bool operator<(const Item&) const;
  virtual bool operator>(const Item&) const;
  virtual bool operator==(const Item&) const;

  bool removeOneInventory();
  bool addOneInventory();
  void setInventory(int);

protected:
 int id;
 string sku;
 string title;
 string description;
 string sortString;

 int inventory;

 int inventoryOut;
 
 static int itemCount;
 

 //string if there is an error
 string error;
};




#endif

