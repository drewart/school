#include "CommandQueue.h"
// note -- destructor, copy constructor, clear, isFull are missing
//      -- subject to typos

//------------------------------ constructor ---------------------------------
CommandQueue::CommandQueue() {
   front = rear = NULL;
}

//------------------------------ ~Queue() -------------------------------------
// 

CommandQueue::~CommandQueue()
{
   cout << "~CommandQueue()" << endl;
   clear();
}

//------------------------------ isEmpty -------------------------------------
// check to see if queue is empty
bool CommandQueue::isEmpty() const {
   return (front == NULL);
}

void CommandQueue::clear()
{
   Command* tran;
   while(dequeue(tran))
     delete tran;
}

//------------------------------ enqueue -------------------------------------
// insert item into rear of queue
bool CommandQueue::enqueue(Command* dataptr) 
{                    

   Node* nodeptr = new Node;                      
   //assert(nodeptr != NULL);
   nodeptr->data = dataptr;
   nodeptr->next = NULL;

   // link at front if empty, otherwise at the rear
   if (isEmpty())
      front = nodeptr;                            
   else
      rear->next = nodeptr;                       
   rear = nodeptr;                                // either way, rear is set
   return true;
}

//---------------------------------- dequeue ---------------------------------
// remove item from front of queue
bool CommandQueue::dequeue(Command*& dataptr) {                    
   if (isEmpty())
      return false;
   
   dataptr = front->data;                  
   Node* nodeptr = front;
   front = front->next;              
   if (isEmpty())
      rear = NULL;                   // if it's the last node in list
   delete nodeptr;
   nodeptr = NULL;
   return true;
}

//---------------------------------- peek ------------------------------------
// return item at front of queue
bool CommandQueue::peek(Command*& dataptr) const {                    
   if (isEmpty())
      return false;
   
   dataptr = front->data;
   return true;
}
/*
#include "queue.h"


Queue::Queue() {
   front = rear = NULL;
}

Queue::~Queue()
{

}

bool Queue::isEmpty() const
{
   cout << "TODO: Queue::isEmpty()";
   return false;
}
   bool Queue::enqueue(Command* tran)                   // insert an item into the queue
   {
      cout << "TODO: bool Queue::enqueue(Command*)";
      return false;
   }

   bool Queue::dequeue(Command*& tran)                   // remove an item 
   {
      cout << "TODO: Queue::dequeue(Command*&)";
      return false;
   }

   bool Queue::peek(Command*& tran) const               // return the next item to remove
   {
      cout << "TODO: Queue::peek(Command*&)";
      return false;
   }
   */



