#include "CustomerHashTable.h"

//------------------------------------------------------------------------------
// Function 
// description
//
//
CustomerHashTable::CustomerHashTable()
{
  size = CUSTOMER_HASH_TABLE_SIZE;
  table = new CustKeyValuePair*[size];
  for (int i = 0; i < size; i++)
  {
    table[i] = NULL;
  }

}

//------------------------------------------------------------------------------
// Function 
// description
//
//
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

//------------------------------------------------------------------------------
// Function 
// description
//
//
bool CustomerHashTable::add(int key,Customer* value)
{
  //int hash = getHash(key) % size;
  int hash = key % size;

  int i = 0;
  while(table[hash] != NULL && table[hash]->key != key && i > size)
  {
    hash = (hash + 1) % size;
    i++;
    if (i > 1000)
    {
      cout << "CustomerHashTable bad hash" << endl;
      return false;
    }

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

//------------------------------------------------------------------------------
// Function 
// description
//
//
Customer* CustomerHashTable::get(int key)
{
  Customer* customer = NULL;
  //int hash = getHash(key);
  int hash = key % size;

  int i = 0;
  while(table[hash] != NULL && table[hash]->key != key && i > size)
  {
    hash = (hash + 1) % size;
    if (i > 1000)
    {
      cout << "CustomerHashTable bad hash" << endl;
      return false;
    }
    i++;
  }

  if (table[hash] != NULL && table[hash]->key == key)
    customer = table[hash]->value;
  
  return customer;
}

//------------------------------------------------------------------------------
// Function 
// description
//
//
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



