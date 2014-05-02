#ifndef MOVIEHASHTABLE_H
#define MOVIEHASHTABLE_H


#include "Movie.h"

using namespace std;

const int HASH_TABLE_SIZE=3571;    //3571 is prime #
//int[]  = {

struct KeyValuePair
{
    string key;
    Movie* value;
};

class MovieHashTable
{

public:
  MovieHashTable();
  MovieHashTable(int);
  ~MovieHashTable();
  bool add(string key,Movie* value);
  bool containsKey(string key);
  Movie* get(string key);


private:
  int getHash(const string &key) const;
  KeyValuePair **table;
  int size;


};

#endif

