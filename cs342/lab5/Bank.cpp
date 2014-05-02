#include "Bank.h"



Bank::Bank()
{
   clientTree = new BSTree();
   transQueue = new Queue();
}

Bank::~Bank()
{
   delete clientTree;
   delete transQueue;
}

bool Bank::loadClients(ifstream& stream)
{
   Client *client;
   do 
   {
      client = new Client();
      if (client->setData(stream))
      {
         clientTree->insert(client);
      }
      else
      {
         delete client;
      }
   }
   while(!stream.eof());

   
   return true;
}

//
bool Bank::loadTransactions(ifstream& stream)
{
   Transaction *tran;
   do 
   {
      //NOTE not queuing invalid Transactions

      tran = new Transaction();
      if (tran->setData(stream))
         transQueue->enqueue(tran);
      else 
      {
        
         if (!stream.eof() && tran->result == Transaction::InvalidInput)   //ignore last read error
         {
           
            switch(tran->result)
            {
               case Transaction::InvalidInput:
                  cout << "Invalid Input " << tran->clientId << "requested" << endl;
                  break;
               case Transaction::InvalidClientAccount:
                  cout << "Unknown client ID " << tran->clientId << "requested" << endl;
                  break;
               //program error
               case Transaction::BadAccountNumber:
                  cout << "Bad Client Account Number" << tran->accountNumber << " for Client" << tran->clientId << endl;
                  break;
               case Transaction::InvalidAmount:
                  cout << "Invalid Amount" << endl;
                  break;
               case Transaction::UnknownType:
                  cout << "Unknown transaction type '" << tran->Type << "' requested" << endl;
                  break;
            }
           
         }
         delete tran;  //delete new tran if invalid
      }

   } while(!stream.eof());
   return true;
}


void Bank::processQueue()
{
   Transaction* tran;
   while(transQueue->dequeue(tran))
   {
      if (!handleTransaction(tran))
         cout << "Unable to handle Transaction" << endl;
      //else TODO:  if not handled do we want to delete the tran?
         //delete tran; ??
   }
}


//handleTransaction
bool Bank::handleTransaction(Transaction* tran)
{
   
   //tran->clientId
   Client *client,*toClient;
   //look up client
   client=toClient=NULL;

   tran->error = !clientTree->find(tran->clientId,client);
   if (tran->Type == TRANSACTION_MOVE && tran->toAccountNumber > 0)
      tran->error = !clientTree->find(tran->toClientId,toClient);

   if (tran->error 
         || client == NULL 
         || (tran->Type == TRANSACTION_MOVE && toClient==NULL))
   {
      tran->result = Transaction::UnknownClient;
      cout << "Unknown client ID " << tran->clientId;
      if (tran->toAccountNumber > 0)
         cout << " or " << tran->toClientId;
      cout << " requested" << endl;
      delete tran;
   }
   else
   {
      //cout << "found client" << client->first << " " << client->last << endl;
      
      switch (tran->Type) 
      {
         case TRANSACTION_DEPOSIT: 
            tran->error = !client->addToAccount(tran->accountNumber,tran->amount);
            //note this will not give a false, always true
            if (tran->error)
               cout << "Deposit not performed on " << client->getAccountName(tran->accountNumber) 
               << " for client " << tran->clientId << endl;
            else
               tran->result = Transaction::Completed;
            break;
         case TRANSACTION_WITHDRAW: 
            tran->error = !client->removeFromAccount(tran->accountNumber,tran->amount);
            if (tran->error)
            {
               tran->result = Transaction::InsufficentFunds;

            }
            else
               tran->result = Transaction::Completed;
            break;
         case TRANSACTION_MOVE:
            tran->error = !client->removeFromAccount(tran->accountNumber,tran->amount);
            if (tran->error)
               tran->result = Transaction::InsufficentFunds;
            else 
            {
               tran->error = !toClient->addToAccount(tran->toAccountNumber,tran->amount);

               if (!tran->error) 
               {
                  Transaction* toClientTran = new Transaction(*tran);
                  toClientTran->result = Transaction::Completed;
                  toClient->addHistory(toClientTran);
               }
               else
                  cout << "Deposit Error Client ID " << tran->toAccountNumber << endl;
             }
             break;
         case TRANSACTION_HISTORY: 
             client->displayHistory();
             break;
                       
      }//end switch

      //error message

      if (tran->error && tran->result == Transaction::InsufficentFunds)
      {
         cout << endl << "Withdrawal not performed on" << client->getAccountName(tran->accountNumber) 
         << " for client " << tran->clientId << endl
         << "\tinsufficient funds" << endl << endl;
      }
      
      if (!tran->error)
         client->addHistory(tran);
      else
	delete tran;	//unable to add transaction
   }//end find clients
   return true;
}//end handleTransaction


//
//
//
void Bank::displayClientAccounts() const
{

   cout << endl << "REPORT" << endl << endl;

   clientTree->display();
}//end displayClientAccounts
