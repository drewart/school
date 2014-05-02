#include "Command.h"

int Command::cmdCount = 0;

Command::Command()
{
  customerId = 0;
   cmdCount++;
}

Command::~Command()
{
  cout << "~Command" << cmdCount-- << endl;

}

string Command::getCommandName() const
{
    return commandName;
}


int Command::getCustomerId() const
{
    return customerId;
}
