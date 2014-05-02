
#include "client.h"


Client::Client()
{
   accountInit=false;
   history=NULL;
}


Client::~Client()
{
   if (accountInit) 
   {
     for(int i = 0; i < 10 ; i++) {
	delete accounts[i];
	accounts[i] = NULL;
     }
   }
   
   if (history != NULL)
      delete history;
}

bool Client::setData(ifstream& stream)
{
   if (stream.eof())
      return false;

      stream >> this->last >> this->first >> this->id;
      if (last.length() == 0 || first.length() == 0 || id <= 0)
         return false;

      Account* account;
      int initBalance; 
      for(int i=0;i<10;i++)
      {
         stream >> initBalance;
         account = new Account;
         account->currentBalance = account->initialBalance = initBalance;
         accounts[i] = account; 
      }
      accountInit=true;


   return true;
}

bool Client::operator<(const Client& client) const
{
   return (this->id < client.id);
}

bool Client::operator>(const Client& client) const
{
   return (this->id > client.id);
}

bool Client::operator==(const Client& client) const
{
   return (this->id == client.id);
}

Client& Client::operator=(const Client& client)
{
   if (this != &client)
   {
      this->id = client.id;
      this->first = client.first;
      this->last = client.last;
      this->history = client.history;
      //delete [] this->accounts;
      for(int i = 0; i < CLIENT_MAX_ACCOUNTS; i++)
         this->accounts[i] = client.accounts[i];
   }
   return *this;
}

string Client::getAccountName(int account) const
{
   string str;
   
   switch(account) 
   {
      case 0: str = "Money Market";         break;
      case 1: str = "Prime Money Market";   break;
      case 2: str = "Long-Term Bond";       break;
      case 3: str = "Short-Term Bond";      break;
      case 4: str = "500 Index Fund";       break;
      case 5: str = "Capital Value Fund";   break;
      case 6: str = "Growth Equity Fund";   break;
      case 7: str = "Growth Index Fund";    break;
      case 8: str = "Value Fund";           break;
      case 9: str = "Value Stock Index";    break;
   }
   return str;
}

   //
   //
   //
   bool Client::addToAccount(int accountIndex,int amount)
   {
      accounts[accountIndex]->currentBalance += amount;
      return true;
   }

   //
   //
   //
   bool Client::removeFromAccount(int accountIndex,int amount)
   {
      if (accounts[accountIndex]->currentBalance >= 0 && accounts[accountIndex]->currentBalance >= amount)
      {
         accounts[accountIndex]->currentBalance -= amount;
         return true;
      } 
      //overdraft protection edge cases
      else if (accountIndex == MoneyMarket || accountIndex == PrimeMoneyMarket)
      {
         return overdraft(accountIndex,MoneyMarket,PrimeMoneyMarket,amount);
      }
      else if (accountIndex == LongTermBond || accountIndex == ShortTermBond)
      {
         return overdraft(accountIndex,LongTermBond,ShortTermBond,amount);
      }
      else
         return false;
         
   }

   //
   //overdraft logic for money market and bonds accounts
   //
   bool Client::overdraft(int accountIndex,int AIndex,int BIndex,int amount)
   {
         if ((accounts[AIndex]->currentBalance + accounts[BIndex]->currentBalance) >= amount)
         {
            amount = amount - accounts[accountIndex]->currentBalance;
            
            accounts[accountIndex]->currentBalance = 0;        //zero out account

            //pick the other account
            int index = (accountIndex == AIndex) ? BIndex : AIndex;  

            accounts[index]->currentBalance -= amount;         // subtract left over
            //add move / overdraft to history
            Transaction* tran = new Transaction(TRANSACTION_MOVE,id,index,amount,id,accountIndex);
            tran->result = Transaction::Completed;
            if (!tran->error)
               addHistory(tran);
            
            return true;
         }
         else 
            return false;
   }//end overdraft


/******************************************************************************
Displays history

*/
   void Client::addHistory(Transaction* tran)
   {
      if (history==NULL)
         history = new LinkList<Transaction>();

      history->Add(tran);
   }

/******************************************************************************
Displays history

*/
void Client::displayHistory() const
{
   if (history == NULL)
      return;
   cout << endl;
   cout << "History of transactions for client " 
        << first << " " << last << ", client ID = " 
        << id << endl;
   cout << "Type      Amount  Detail" << endl;
   cout << "--------- ------- --------------------------------------" << endl;

   //NOTE using custom coded iterator
   //history->print();

   LinkList<Transaction>::iterator it(*history); 
   
   Transaction tran;
   while(it.MoveNext())
   {
      tran = it.item();
      switch(tran.Type)
      {
         case TRANSACTION_HISTORY:
            cout << tran.getTransactionName() << endl;
            break;
         case TRANSACTION_DEPOSIT:
         case TRANSACTION_WITHDRAW:
               cout << (tran.Type == TRANSACTION_DEPOSIT ? "deposit   $" : "withdraw  $") 
                     << setw(6) << tran.amount 
                     << (tran.Type == TRANSACTION_DEPOSIT ? " into " : " from ")
                     << getAccountName(tran.accountNumber) << endl; 
               break;
         case TRANSACTION_MOVE:
               cout << "move      $" << setw(6) << tran.amount 
                     << " from " << getAccountName(tran.accountNumber) << endl 
                     << setw(21) << "to " << getAccountName(tran.toAccountNumber) 
                     << " for client " << tran.toClientId << endl;
      }//end switch
   }//end while
   cout << endl;
}//end displayHistory


int Client::getAccountBalance(int i) const
{
   if (i < 0 || i > 9)
      return 0;

   return this->accounts[i]->currentBalance;
}

/******************************************************************************
client output

*/
ostream& operator<< (ostream& out, const Client & client)
{
   
   out << endl << client.id << "  " << client.first<< " " << client.last;
   
   out << endl << "Initial Balances: ";

   for(int i = 0; i < CLIENT_MAX_ACCOUNTS; i++)
   {
      out << setw(6) << client.accounts[i]->initialBalance;
   }

   out << endl << "Final Balances:   ";

   for(int i = 0; i < CLIENT_MAX_ACCOUNTS; i++)
   {
      out << setw(6) << client.accounts[i]->currentBalance;
   }
   return out;
}
