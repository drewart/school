
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


const char TRANSACTION_DEPOSIT   = 'D';
const char TRANSACTION_WITHDRAW  = 'W';
const char TRANSACTION_MOVE      = 'M';
const char TRANSACTION_HISTORY   = 'H';

class Transaction {

friend ostream& operator<< (ostream& out, const Transaction&);

public:
   //state of the Transaction
   enum ResultState {
      NoError,
      InvalidInput,
      Completed,
      UnknownType,
      InvalidAmount,
      InvalidClientAccount,
      BadAccountNumber,
      UnknownClient,
      InsufficentFunds
   };

   Transaction();
   Transaction(const Transaction&);
   Transaction(char,int,int,int,int,int);
   
   ~Transaction();

   Transaction& operator=(const Transaction&);

   bool setData(ifstream&);  //reads from ifstream
      
   char Type;                    // letter for transaction
   int clientId;             // 4 digit accountNumber
   int accountNumber;            // 1 digit sub account number
   int toClientId;           // 
   int toAccountNumber;          //
   int amount;                   //amount of transaction

   //error & transaction handling
   bool error;
   enum ResultState result;
   string errorMessage;
   
   //display
   string getTransactionName() const;

  

   

private:
   int transactionId;
   bool validTransaction();
   static int transactionCount;

};


#endif
