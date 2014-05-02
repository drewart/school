#include "transaction.h"

//init num of transaction objects
int Transaction::transactionCount=0;
//
//
//
Transaction::Transaction()
{
   ++transactionCount;
   transactionId=transactionCount;
   Type='0';
   clientId=-1;
   accountNumber=-1;
   amount=-1;
   toClientId=-1;
   toAccountNumber=-1;
   error=false;
   errorMessage = "";
   result = NoError;
}

//
//
//
Transaction::Transaction(const Transaction& tran)
{
   ++transactionCount;
   transactionId=transactionCount;
   Type=tran.Type;
   clientId=tran.clientId;
   accountNumber=tran.accountNumber;
   amount=tran.amount;
   toClientId=tran.toClientId;
   toAccountNumber=tran.toAccountNumber;
   error=tran.error;
   errorMessage = tran.errorMessage;
   result = tran.result;
}

Transaction::Transaction(char type,int client1,int account1,int inAmount,int client2,int account2)
{
   ++transactionCount;
   transactionId=transactionCount;
   Type=type;
   clientId=client1;
   accountNumber=account1;
   amount=inAmount;
   this->toClientId=client2;
   toAccountNumber=account2;
   
   error = false;
   result = NoError;
   errorMessage = "";

   error = !validTransaction();
   if (error)
      result = InvalidInput;
}

//
//
//
Transaction::~Transaction()
{
   --transactionCount;
   //DEBUG cout << "deleting " << transactionCount << endl;
}


Transaction& Transaction::operator=(const Transaction& tran)
{
   if (this != &tran)
   {
      Type=tran.Type;
      clientId=tran.clientId;
      accountNumber=tran.accountNumber;
      amount=tran.amount;
      toClientId=tran.toClientId;
      toAccountNumber=tran.toAccountNumber;
      error=tran.error;
      errorMessage = tran.errorMessage;
      result = tran.result;
   }
   
   return *this;
}

//
//
//
bool Transaction::setData(ifstream& stream)
{
   int clientId;
   
   //read in first char
   stream >> this->Type;

   //read error & eof
   if (this->Type == '0')
   {
      error = true;
      result = InvalidInput;
      return false;
   }

   //read in client # & account
   stream >> clientId;

   if (Type == TRANSACTION_HISTORY)
   {
      this->clientId = clientId;
   }
   else
   {
      this->clientId = clientId / 10;
      this->accountNumber = clientId % 10;
   
      //read in amount
      stream >> this->amount;
   }
   

   //read in accout for move Transaction
   if (this->Type == TRANSACTION_MOVE)
   {
      stream >> clientId;
      this->toClientId = clientId / 10;
      this->toAccountNumber = clientId % 10;
   }

   

   return validTransaction();
}

//
//
//
bool Transaction::validTransaction()
{

   if (!(Type == TRANSACTION_DEPOSIT || Type == TRANSACTION_MOVE || Type == TRANSACTION_WITHDRAW || TRANSACTION_HISTORY))  //valid type
   {
      result = UnknownType;
      error = true;
      return !error;
   }

   if (clientId < 0 || clientId > 9999) //clinet account # limits
   {
      error = true;
      result = InvalidClientAccount;
   }
   
   if (Type == TRANSACTION_HISTORY)      //if History no need to check the rest
      return !error;                     //if not error then valid
   

   if (accountNumber < 0 || accountNumber > 9)  //acountNumber limits
   {
      result = BadAccountNumber;
      error = true;
   }

   if (amount < 0)      //amount lower limit, no max limit
   {
      result = InvalidAmount;
      error = true;
   }


   
   if (Type == TRANSACTION_MOVE  && (toClientId < 0 || toClientId > 9999))       //valid move account
   {
      result = InvalidClientAccount;
      error = true;
   }
   return !error;       //if not error then valid
}

string Transaction::getTransactionName() const
{
   string str;
   
   switch (Type) 
   {
      case TRANSACTION_DEPOSIT:  str = "deposit";  break;
      case TRANSACTION_WITHDRAW: str = "withdraw"; break;
      case TRANSACTION_MOVE:     str = "move";     break;
      case TRANSACTION_HISTORY:  str = "history";  break;
   }

   return str;
}



ostream& operator<< (ostream& out, const Transaction& tran)
{
   //header
   out << tran.getTransactionName() << " " << tran.amount << endl;
   return out;
}
