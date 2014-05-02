#include "queue.h"
// note -- destructor, copy constructor, clear, isFull are missing
//      -- subject to typos

//------------------------------ constructor ---------------------------------
Queue::Queue() {
   front = rear = NULL;
}

//------------------------------ ~Queue() -------------------------------------
// 

Queue::~Queue()
{
   clear();
}

//------------------------------ isEmpty -------------------------------------
// check to see if queue is empty
bool Queue::isEmpty() const {
   return (front == NULL);
}

void Queue::clear()
{
   Transaction* tran;
   while(dequeue(tran))
     delete tran;
}

//------------------------------ enqueue -------------------------------------
// insert item into rear of queue
bool Queue::enqueue(Transaction* dataptr) 
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
bool Queue::dequeue(Transaction*& dataptr) {                    
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
bool Queue::peek(Transaction*& dataptr) const {                    
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
   bool Queue::enqueue(Transaction* tran)                   // insert an item into the queue
   {
      cout << "TODO: bool Queue::enqueue(Transaction*)";
      return false;
   }

   bool Queue::dequeue(Transaction*& tran)                   // remove an item 
   {
      cout << "TODO: Queue::dequeue(Transaction*&)";
      return false;
   }

   bool Queue::peek(Transaction*& tran) const               // return the next item to remove
   {
      cout << "TODO: Queue::peek(Transaction*&)";
      return false;
   }
   */


