#include "Command.h"

struct CommandNode 
{
  Command* command;
  CommandNode* next;
};

const int COMMAND_FACTORY_HASH_SIZE = 26;

class CommandFactory
{
  
public:
  static Command* createCommand(char c);
  static void cleanUp();

private:
   CommandFactory();
  ~CommandFactory();
  static CommandFactory* getInstance();

  Command* createCommandImpl(char c);
   
  int hash(char c);
    
  static bool instanceCreated;
  static CommandFactory *factory;
  
  void addCommand(Command*);

  Command* commands[COMMAND_FACTORY_HASH_SIZE];

  CommandNode* firstCommand;
  CommandNode* lastCommand;

  int commandCount;


};

