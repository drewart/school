#ifndef CUSTOMER_HASH_TABLE_H
#define CUSTOMER_HASH_TABLE_H


#include "Customer.h"

using namespace std;

const int CUSTOMER_HASH_TABLE_SIZE=3571;    //3571 is prime #
//int[]  = {

struct CustKeyValuePair
{
    int key;
    Customer* value;
};

class CustomerHashTable
{

public:
  CustomerHashTable();
  ~CustomerHashTable();
  bool add(int key,Customer* value);
  bool containsKey(int key);
  Customer* get(int key);


private:
  //int getHash(const int key) const;
  CustKeyValuePair **table;
  int size;


};

#endif

