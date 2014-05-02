#include "CustomerHashTable.h"

CustomerHashTable::CustomerHashTable()
{
  size = CUSTOMER_HASH_TABLE_SIZE;
  table = new CustKeyValuePair*[size];
  for (int i = 0; i < size; i++)
  {
    table[i] = NULL;
  }

}


CustomerHashTable::~CustomerHashTable()
{

  for(int i = 0; i < size; i++)
    if (table[i] != NULL)
    {
      delete table[i]->value;
      delete table[i];
    }

   delete []table; 

}

bool CustomerHashTable::add(int key,Customer* value)
{
  //int hash = getHash(key) % size;
  int hash = key % size;

  int i = 0;
  while(table[hash] != NULL && table[hash]->key != key && i < size)
  {
    hash = (hash + 1) % size;
    i++;
  }

  if (i >= size)
  {
    cout << "CustomerHashTable size limit reached" << endl;
    return false;
  }


  if (table[hash] != NULL)
    return false;

  table[hash] = new CustKeyValuePair;
  table[hash]->key = key;
  table[hash]->value = value;

  return true;
}

Customer* CustomerHashTable::get(int key)
{
  Customer* customer = NULL;
  //int hash = getHash(key);
  int hash = key % size;

  int i = 0;
  while(table[hash] != NULL && table[hash]->key != key && i < size)
  {
    hash = (hash + 1) % size;
    i++;
  }

  if (table[hash] != NULL && table[hash]->key == key)
    customer = table[hash]->value;
  
  return customer;
}

bool CustomerHashTable::containsKey(int key)
{
   //int hash = getHash(key);
  int hash = key % size;

  int i = 0;
  while(table[hash] != NULL && table[hash]->key != key && i < size)
  {
    hash = (hash + 1) % size;
    i++;
  }

  if (table[hash] != NULL && table[hash]->key == key)
    return true;
  else
    return false;
}

/*
int CustomerHashTable::getHash(const string &key) const
{

  int h = 0;
  int l = key.length();
  for (int i=0; i < l; i+=2)
     h += (key[i] ^ l-i);
  return h;
}
*/

