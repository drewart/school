#include "CommandList.h"
#include "Command.h"


CommandList::CommandList() 
{
   head = tail = NULL;
}

CommandList::~CommandList() 
{
  //cout << "~CommandList()" << endl;
    while (head != NULL)
    {
       Node* save = head;
       head = head->next;
       save->cmd = NULL;
       save->next = NULL;
       delete save;  
       save = NULL;
    }
    tail = NULL;
}
        
void CommandList::add(Command* cmd) {
   Node* node = new Node();
   node->cmd = cmd;
   node->next = NULL;
   
   if (head == NULL)
     head = tail = node;
   else
   {
  
     tail->next = node;                          
     tail = node;

   }
}
        
void CommandList::printList() {
   for (Node* p = head; p != NULL; p = p->next)
      p->cmd->write(cout); 
}



