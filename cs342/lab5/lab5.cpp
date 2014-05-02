#include <iostream>
#include "client.h"
#include "Bank.h"
//  
//  http://courses.washington.edu/css342/zander
//  http://courses.washington.edu/css342/zander/Labsf11s12/lab5s12.pdf
//
//
using namespace std;

//DEBUG void testClient();

int main() 
{
   //system("cmd /c copy /y *.txt .\\Debug\\.");
   //system("cmd /c copy /y *.txt ..\\Debug\\.");

   //testClient();

   ifstream clientFile("lab5data.txt");
   if (!clientFile) {
      cout << "File could not be opened." << endl;
      return 1;
   }

   ifstream commandFile("lab5commands.txt");
   if (!commandFile) {
      cout << "File could not be opened." << endl;
      return 1;
   }

   Bank bank;

   bank.loadClients(clientFile);
   bank.loadTransactions(commandFile);

   bank.processQueue();
   bank.displayClientAccounts();
      

   return 0;
}


void testClient()
{
   //system("cmd /c copy /y *.txt .\\Debug\\.");

   ifstream clientTestFile("testclient.txt");
   if (!clientTestFile)
   {
      cout << "failure loading lab5clienttest.txt";
         return;
   }

   Client *client = new Client();
   client->setData(clientTestFile);

   if (client->id != 5555)
      cout << "fail id"<< endl;
   if (client->first != "daffy")
      cout << "fail first"<< endl;

   if (client->last != "duck")
      cout << "fail last"<< endl;

   if (client->getAccountBalance(0) != 4500)
      cout << "error 0 account" << endl;

   if (client->getAccountBalance(1) != 500)
      cout << "error 1 account" << endl;
   for(int i=2; i < 10; i++)
   {
      if (client->getAccountBalance(i) != 0)
      {
         cout << cout << "error " << i << " account" << endl;
      }
   }

   client->addToAccount(0,500);
   if (client->getAccountBalance(0) != 5000)
      cout << "error addToAccount" << endl;

   client->removeFromAccount(0,1000);
   if (client->getAccountBalance(0) != 4000)
      cout << "error removeFromAccount" << endl;

   client->removeFromAccount(0,4000);
   if (client->getAccountBalance(0) != 0)
      cout << "error removeFromAccount all" << endl;

   if (!client->removeFromAccount(0,1))
      cout << "fail overdraft a" << endl;

   if (client->getAccountBalance(0) != 0)
      cout << "fail overdraft b" << endl;

   if (client->getAccountBalance(1) != 499)
      cout << "fail overdraft c" << endl;

   client->addToAccount(2,1);
   if (client->getAccountBalance(2) != 1)
      cout << "fail add to 0" << endl;

   //test overdraft a + b = 1 - 2 = false
   bool assert_false = client->removeFromAccount(3,2);
   if (assert_false)
      cout << "fail overdraft d" << endl;
   
   if (client->getAccountBalance(2) != 1)
      cout << "fail overdraft e" << endl;

   if (client->getAccountBalance(3) != 0)
      cout << "fail overdraft f" << endl;
}

