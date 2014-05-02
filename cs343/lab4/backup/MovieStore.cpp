#include "MovieStore.h"
#pragma region Contstructors {{{
//{{{MovieStore
MovieStore::MovieStore(string storeName)
{
   name = storeName;
}

MovieStore::~MovieStore()
{
  cout << "~MovieStore()" << endl;
}
//}}}
#pragma endregion }}}



//{{{addProduct
bool MovieStore::addItem(Item* item)
{
   return movieTree.insert(item);
}
//}}}

//{{{
bool MovieStore::findItem(string key, Item*& foundItem)
{
  return this->movieTree.find(key,foundItem);
}
//}}}


void MovieStore::displayStore() const
{
  cout << "*IN* *OUT*" << endl;
  
  cout << " DVD  DVD  TITLE                DIRECTOR         YEAR MO ACTOR" << endl;
  this->movieTree.display();
}

void MovieStore::displayCustomerHistory(int id) const
{
  cout << "display customer history:" << id << endl;
}


bool MovieStore::checkoutItem(Item* item)
{


  return false;
}

bool MovieStore::returnItem(Item* item)
{

  return false;
}

