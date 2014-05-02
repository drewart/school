#include "Command.h"

struct CommandNode 
{
  Command* command;
  CommandNode* next;
};

const int COMMAND_FACTORY_HASH_SIZE = 26;

//------------------------------------------------------------------------------
// CommandFactory 
//   creates commands to run on a Store of Items
//
//
class CommandFactory
{
  
public:
  //static method for creating command objects
   static Command* createCommand(char c);
  
  //static method for clean up objects
  static void cleanUp();

private:
   //private for singleton
   CommandFactory();
  ~CommandFactory();
  
  //get private instance of factory
  static CommandFactory* getInstance();

  //impl of the create command
  Command* createCommandImpl(char c);
   
  //hash method
  int hash(char c);
    
  //static bool if the static sigle factory is created
  static bool instanceCreated;
  
  //static instance of the factory
  static CommandFactory *factory;
  
  //add command to local pointer storage
  void addCommand(Command*);

  //hash table
  Command* commands[COMMAND_FACTORY_HASH_SIZE];
  
  //Nodes for storing list of Commands
  CommandNode* firstCommand;
  CommandNode* lastCommand;

  int commandCount;


};

