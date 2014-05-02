#include "Item.h"

//static 
int Item::itemCount = 0;

Item::Item()
{
  inventory = 0;
  itemCount++;
}

Item::~Item()
{
  cout << "~Item() " << itemCount << endl;
  itemCount--;
}

string Item::getTitle() const
{
  return title;
}

int Item::getId() const
{
  return id;
}

void Item::setId(int id)
{
  this->id = id;
}

string Item::getSku() const
{
  return sku;
}

void Item::setSku(string s)
{
  this->sku = s;
}

string Item::getError() const
{
  return error;
}

string Item::getSortString()
{
  return sortString;
}


bool Item::addOneInventory()
{
  if (inventoryOut > 0)
  {
    inventoryOut--;
    inventory++;
    return true;
  }
  return false;
}

bool Item::removeOneInventory()
{
  if (inventory > 0)
  {
    inventoryOut++;
    inventory--;
    return true;
  }
  return false;
}

void Item::setInventory(int inv)
{
  inventory = inv;
}



bool Item::setData(ifstream& stream)
{
  char c;
  stream >> c;
  stream.ignore(1);  //skip space
  getline(stream,title);
  //sortString = title;
  return !stream.eof();
}


//valid item, has a title
bool Item::valid()
{
  return (title.length() > 0);

}

void Item::write(ostream& out) const
{
  out << title;
}

int Item::compareTo(Item* item) const
{
  if (sortString == item->sortString)
    return 0;
  else if (sortString < sortString)
    return -1;
  else 
    return 1;
}

bool Item::operator<(const Item& item) const
{
  return sortString < item.sortString;
}
  
bool Item::operator>(const Item& item) const
{
  return sortString > item.sortString;
}
  
bool Item::operator==(const Item& item) const
{
   return (sortString == item.sortString);
}
  
ostream& operator<< (ostream&out, const Item &item)
{
  item.write(out); 
  return out;
}

