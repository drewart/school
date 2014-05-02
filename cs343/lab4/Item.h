//product.h
#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <fstream>
#include <string>

//----------------------------------------------------------------------------
// class Item 
//  generic class for products and store items with base public and protected fields
//
//
// Assumptions:
//    -- 
//    -- 
//       
//    -- 
//    -- 
//       
//----------------------------------------------------------------------------

using namespace std;

class Item
{

  	friend ostream& operator<< (ostream&, const Item &);

public:
  Item();
  ~Item();

  //generic metods for a Item {{{
  int getId() const;
  void setId(int);

  string getSku() const;
  void setSku(string);

  string getTitle() const;

  string getError() const;

  string getSortString();

  
  virtual void write(ostream&) const;

  virtual void writeBasic(ostream&) const;

  virtual bool setData(ifstream&);

  virtual bool valid();

  //}}}
  
  //compare
  virtual int compareTo(Item*) const;
  
  virtual bool operator<(const Item&) const;
  virtual bool operator>(const Item&) const;
  virtual bool operator==(const Item&) const;

  //inventory methods
  bool removeOneInventory();
  bool addOneInventory();
  void setInventory(int);

//protected fields
protected:
 int id;
 string sku;
 string title;
 string description;
 string sortString;

 //product/item inventory tracking
 int inventory;

 int inventoryOut;
 
 static int itemCount;
 

 //string if there is an error
 string error;
};




#endif

