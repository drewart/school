#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
//#include <iomanip>
#include <fstream>
#include <string>

#include "CommandList.h"

using namespace std;

class Command;

class Customer 
{
	
	friend ostream& operator<< (ostream&, const Customer &);

public:
	Customer();	                    //default constructor
	Customer(const Customer&);	                    //default constructor
	~Customer();
  int getId();
  string getName() const;
	bool setData(ifstream&);                	//sets data from file
  void addHistory(Command*);
  void printHistory();
	bool operator<(const Customer&) const;   	//compare Customer id
	bool operator>(const Customer&) const;    	//compare Customer id
	bool operator==(const Customer&) const;   	//compare Customer id
	void write(ostream&) const;   	//compare Customer id

private:
  int id;				                //Customers id #
	string name;					        //last name of Customer

  CommandList history;

};

#endif


