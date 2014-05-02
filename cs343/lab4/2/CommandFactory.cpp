#include "CommandFactory.h"

#include "CommandBarrow.h"
#include "CommandReturn.h"
#include "CommandShowStore.h"
#include "CommandHistory.h"


//private factory instance created
bool CommandFactory::instanceCreated = false;

//private singleton instance of factory
CommandFactory* CommandFactory::factory=NULL;
//int CommandFactory::commandCount = 0;

//------------------------------------------------------------------------------
// CommandFactory
// Creates Command objects to run on the store
// this uses a hash table
//  also used an a pointer/memory management
// this holds all the pointers
//
//
//



//{{{CommandFactory
//------------------------------------------------------------------------------
// CommandFactory
// Creates Command objects to run on the store
// this uses a hash table
//
//
CommandFactory::CommandFactory()
{
  firstCommand = lastCommand = NULL;

  //default to NULL
  for(int i = 0; i < COMMAND_FACTORY_HASH_SIZE; i++)
  {
    commands[i] = NULL;
  }

  //set commands
  commands[CommandBarrow::Letter    -'A'] = new CommandBarrow();
  commands[CommandReturn::Letter    -'A'] = new CommandReturn();
  commands[CommandShowStore::Letter -'A'] = new CommandShowStore();
  commands[CommandHistory::Letter   -'A'] = new CommandHistory();
}
//}}}


//{{{~CommandFactory
//------------------------------------------------------------------------------
//
// ~CommandFactory
//  clean up all created commands
//
CommandFactory::~CommandFactory()
{
  //cout << "~CommandFactory()" << endl;
  
 
  CommandNode* temp = NULL;
  CommandNode* current = firstCommand;
  
  while(current != NULL)
  { 
    temp = current;
    current = current->next;
    delete temp->command; //clean up command
    delete temp; //clean up CommandNode
  }
  firstCommand = lastCommand = NULL;

  for(int i = 0; i < COMMAND_FACTORY_HASH_SIZE; i++)
  {
    if (commands[i] != NULL)
    {
      delete commands[i];
    }
  }

}
//}}}

//{{{getInstance()
//------------------------------------------------------------------------------
// getInstance()
// private internal Singleton getInstance()
//
//
CommandFactory* CommandFactory::getInstance()
{
  if (!instanceCreated)
  {
    factory=new CommandFactory();
    instanceCreated = true;
    return factory;
  }
  else
  {
    return factory;
  }
}
//}}}

//{{{
//------------------------------------------------------------------------------
// createCommand 
// creates a command based on the letter in the data file
//
//
Command* CommandFactory::createCommand(char ch)
{
  return getInstance()->createCommandImpl(ch);
}
//}}}

//------------------------------------------------------------------------------
// cleanUp 
// since the class is static there needs to be a static clean up method
//
//
void CommandFactory::cleanUp()
{
  if (instanceCreated)
  {
    instanceCreated = false;
    delete factory;
    factory = NULL;
  }

}


//------------------------------------------------------------------------------
// createCommandImpl 
// method that createds the classes from the Command hash table
//
//
Command* CommandFactory::createCommandImpl(char ch)
{
 
  Command* cmd=NULL;
  int subscript = hash(ch);
  
  //handle edge cases
  if (subscript < 0 || subscript > 25)
    return cmd;

   if (commands[subscript] != NULL)
     cmd = commands[subscript]->createInstance();

   if (cmd != NULL)
     addCommand(cmd);

   return cmd;
}

int CommandFactory::hash(char ch)
{
    return ch-'A';
}

//------------------------------------------------------------------------------
// addCommand 
// add a command to local memory of commands created
//
//
void CommandFactory::addCommand(Command* cmd)
{
  CommandNode *node = new CommandNode();
  node->command = cmd;
  node->next = NULL;

  if (firstCommand == NULL)
  {
    firstCommand = lastCommand = node;
  } 
  else
  {
    lastCommand->next = node;
    lastCommand = node;
  
  }
    

}//end addCommand


