////////////////////////////////  list.h file  ///////////////////////////////
// Simple linked list, uses Node as linked list node

#ifndef BANK_H
#define BANK_H

//#include "nodedata.h"
#include <iostream>
#include <fstream>
#include "client.h"
#include "BSTree.h"
#include "queue.h"
using namespace std;


//----------------------------------------------------------------------------------------------------
// Bank a driver class for handling loading clients and accounts and processing the transaction queue
//
class Bank
{

public:
	Bank();
	~Bank();	
	bool loadClients(ifstream&);
	bool loadTransactions(ifstream&);
	void processQueue();
	void displayClientAccounts() const;
   
private:
	BSTree* clientTree;
	Queue* transQueue;
	bool handleTransaction(Transaction*);
   bool handleDeposit(Client*,Transaction*);
   bool handleWithdraw(Client*,Transaction*);
   bool handleMove(Client*,Transaction*);
   bool handleHistory(Client*);
};

#endif
