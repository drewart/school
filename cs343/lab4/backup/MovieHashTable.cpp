#include "MovieHashTable.h"

MovieHashTable::MovieHashTable()
{
  size = HASH_TABLE_SIZE;
  table = new KeyValuePair*[size];
  for (int i = 0; i < size; i++)
  {
    table[i] = NULL;
  }

}

MovieHashTable::MovieHashTable(int tableSize)
{
  size = tableSize+1;
  table = new KeyValuePair*[size];
  for (int i = 0; i < size; i++)
  {
    table[i] = NULL;
  }

}

MovieHashTable::~MovieHashTable()
{
   cout << "~MovieHashTable()" << endl;
  for(int i = 0; i < size; i++)
    if (table[i] != NULL)
      delete table[i];

   delete []table; 

}

bool MovieHashTable::add(string key,Movie* value)
{
  int hash = getHash(key) % size;

  int i = 0;
  while(table[hash] != NULL && table[hash]->key != key && i < size)
  {
    hash = (hash + 1) % size;
    i++;
  }
  if (table[hash] != NULL)
    return false;

  table[hash] = new KeyValuePair;
  table[hash]->key = key;
  table[hash]->value = value;

  return true;
}

Movie* MovieHashTable::get(string key)
{
  Movie* movie = NULL;
  int hash = getHash(key);

  int i = 0;
  while(table[hash] != NULL && table[hash]->key != key && i < size)
  {
    hash = (hash + 1) % size;
    i++;
  }

  if (table[hash] != NULL && table[hash]->key == key)
    movie = table[hash]->value;
  
  return movie;
}

bool MovieHashTable::containsKey(string key)
{
   int hash = getHash(key);

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

int MovieHashTable::getHash(const string &key) const
{

  int h = 0;
  int l = key.length();
  for (int i=0; i < l; i+=2)
     h += (key[i] ^ l-i);
  return h;
}

