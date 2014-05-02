//Command
#include "Command.h"

//------------------------------------------------------------------------------


//static count of commands set to 0
int Command::cmdCount = 0;

//------------------------------------------------------------------------------
// Command
// base constructor
//
//
Command::Command()
{
  customerId = 0;
   cmdCount++;
}

//------------------------------------------------------------------------------
//
// ~Command()
// 
//
Command::~Command()
{
   cmdCount--;
  //cout << "~Command" << cmdCount << endl;
}

//------------------------------------------------------------------------------
// getCommandName
//
// name of the command
//
string Command::getCommandName() const
{
    return commandName;
}

//------------------------------------------------------------------------------
// getCustomerId
// gets the customer id if the command needs it default 0
//
//
int Command::getCustomerId() const
{
    return customerId;
}
