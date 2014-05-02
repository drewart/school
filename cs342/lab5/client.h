#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
//#include "list.h"
#include "LinkList.h"
#include "transaction.h"

using namespace std;

const int CLIENT_MAX_ACCOUNTS=10;

//----------------------------------------------------------------------------------------------------
// Client class to hold client and account information
//
class Client 
{

	friend ostream& operator<< (ostream&, const Client &);

public:
    Client();
    ~Client();		

      //
      //NOTE would be better as class an loaded from file or DB
      enum AccountType { MoneyMarket=0,
                     PrimeMoneyMarket=1,
                     LongTermBond=2,
                     ShortTermBond=3, 
                     Index500Fund=4,
                     CapitalValueFund=5,
                     GrowthEquityFund=6,
                     GrowthIndexFund=7,
                     ValueFund=8,
                     ValueStockIndex=9
                  };
   
      bool setData(ifstream&);		//create client object from file stream
	   
      bool operator<(const Client&) const;
	   bool operator>(const Client&) const;
	   bool operator==(const Client&) const;
	   Client& operator=(const Client&);
      string getAccountName(int) const;
      int getAccountBalance(int) const;
	   void displayHistory() const;
      
      string last;					//last name of client
		string first;					//first name of client
		int id;				//clients account #

      struct Account
      {		
         int initialBalance;				//initial balance for account
		   int currentBalance;				//current balance for account

      };//end Account

      bool addToAccount(int,int);
      bool removeFromAccount(int,int);

      void addHistory(Transaction*);

      
      


	private:
		Account* accounts[CLIENT_MAX_ACCOUNTS];		//array to hold 10 accounts
		LinkList<Transaction>* history;			//history collection of trans
      bool accountInit;

      bool overdraft(int,int,int,int);
};//end Client class




#endif
