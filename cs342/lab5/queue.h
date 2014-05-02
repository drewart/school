
#ifndef QUEUE_H
#define QUEUE_H

//#include "nodedata.h"
#include "transaction.h"

//----------------------------------------------------------------------------
// class Queue 
//
// ADT Queue: collection of zero or more items (list) with the restriction that
//            all insertions happen at one end, called the rear of the queue, 
//            and all removals occur at the other end, the front
//            (also known as FIFO -- First In, First Out)
//
// Assumptions:
//    -- assumes NodeData is a class of actual data
//    -- Node (linked list implementation) is a struct made of just
//       a NodeData* and a Node*
//    -- The push allocates memory for a Node, ptr to the data is passed in.
//    -- doesn't have to be NodeData* in queue, data may be stored directly
//       in the Node or array element, e.g. queue of ints, queue of NodeData
//----------------------------------------------------------------------------

class Queue {
   friend ostream &operator<<(ostream&, const Queue&);

public:
   Queue();                                   // default constructor
   ~Queue();                                  // destructor
   Queue(const Queue&);                       // copy constructor
   void clear();                              // clear out queue
   bool isEmpty() const;                      // is the queue empty?
   //bool isFull() const;                       // is the queue full?
   bool enqueue(Transaction*);                   // insert an item into the queue
   bool dequeue(Transaction*&);                  // remove an item 
   bool peek(Transaction*&) const;               // return the next item to remove

private:
   struct Node {              // the node in a linked list
      Transaction* data;         // pointer to actual data, operations in NodeData
      Node* next;
   };

   // for linked list implementation
   Node* front;                               // pointer to front of queue
   Node* rear;                                // pointer to rear of queue

   // for array implementation
   //Transaction* array[MAX];                   // assume MAX is defined
   //Note* front, rear;                       // front is always subscript before 
				          // the true front, rear is true rear
};


#endif

