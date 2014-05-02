////////////////////////////////  list.h file  ///////////////////////////////
// Simple linked list, uses Node as linked list node

#ifndef LIST_H
#define LIST_H

//#include "nodedata.h"
#include <iostream>
#include <fstream>
using namespace std;

//--------------------------  class List  ------------------------------------
// ADT List: finite, ordered collection of zero or more items.
//           The ordering is determined by operator< of NodeData class.
//          
// TODO: copy constructor
// TODO: 
// Assumptions:  
//    -- Control of <, printing, etc. of NodeData information is in the 
//       NodeData class.  
//    -- There is no dummy head node, head points to first node.  
//       If the list is empty, head is NULL.
//    -- The insert allocates memory for a Node, ptr to the data is passed in.
//       is the responsibility of the client. 
//
// Note this definition is not a complete class and is not fully documented.
//----------------------------------------------------------------------------
template <typename T>
class List {
   //friend ostream &operator<<(ostream&, const List<T>&);
  
   //template <typename T>
   friend ostream& operator<<(ostream& output, const List<T>& thelist) {

      typename List<T>::Node* current = thelist.head;
      while (current != NULL) 
      { 
         /*DEBUG: 
         output << "mem:";
         output << current->data;
         output << " object:";
         output << endl;*/

         output << *current->data;
         current = current->next;
      }
      return output;                      // enables output << x << y;
   }

public:
   List() : head(NULL) { }                                   // default constructor
   ~List(void);                                 // destructor
   List(const List<T>&);                  // copy constructor
   bool insert(T*);                     // insert one Node into list
   bool remove(const T&,T*&);           // removes an item from the list
   bool retrieve(const T&,T*&);
   bool isEmpty() const;                       // is list empty?
   void buildList(ifstream&);                  // build a list from datafile
   void makeEmpty();
   void intersect(const List<T>&,const List<T>&);
   void merge(List<T>&,List<T>&);
   
   List<T>& operator=(const List<T>&);

   bool operator==(const List<T>&) const;       //==
   bool operator!=(const List<T>&) const;       //!=

   bool testDataPointerSame(const List<T>&) const;
   bool testNodePointerSame(const List<T>&) const;

private:
   struct Node {              // the node in a linked list
      T* data;         // pointer to actual data, operations in NodeData
      Node* next;
   };

   void copyList(Node*,Node*&) const;



   Node* head;                                 // pointer to first node in list
};


/******************************************************************************
*
* List Copy Con
*
*/
template <typename T>
List<T>::List(const List<T>& list) {
   head = NULL;
   copyList(list.head,head);     // util copy

}//end List(List)

//----------------------------------------------------------------------------
// isEmpty 
// check to see if List is empty
template <typename T>
bool List<T>::isEmpty() const {
   return head == NULL;
}



template <typename T>
List<T>::~List(void) {
	
	this->makeEmpty();	//clears out list
}



template <typename T>
bool List<T>::remove(const T& target,T*& ptrData)
{
   Node *current,*prev;
	prev = NULL;
   current = head;
   while(current != NULL)
   {
      if (*current->data == target)
      {
         //NOTE : IF NEXT =NULL THEN HEAD = NULL
         if (prev==NULL) 
            head = current->next;         //repoint head to next 
         else
            prev->next = current->next;   //remove point prev to next
         
		   ptrData = current->data;         //point to removed node data

         delete current;                  //remove pointer
         current = NULL;                  //set pointer to null
         return true;                     //found target
      }
      prev = current;
	   current = current->next;
     
      //TODO: look at remove
      //delete prev;               //TODO: look at if need to delete node->data
   }
    return false;    //didn't find target
}//end remove


/******************************************************************************
*
* retrieve
*
*/
template <typename T>
bool List<T>::retrieve(const T& target,T*& ptrData)
{
   typename List<T>::Node *current;
	current = head;
   while(current != NULL)
   {
		if (*current->data == target) {

         ptrData = current->data;         //point to removed data
         return true;                     //found target
      }//end if
     
	  current = current->next;  //walk list
   }//end while
   return false;    //didn't find target
}//end retrieve






/***************************** insert *************************************************
* 
* insert
*
*/
template <typename T>
bool List<T>::insert(T* dataptr) {                    

   Node* ptr= new Node;
   if (ptr == NULL) return false;                 // out of memory, bail
   ptr->data = dataptr;                           // link the node to data

   // if the list is empty or if the node should be inserted before 
   // the first node of the list
   if (isEmpty() || *ptr->data < *head->data) {
      ptr->next = head;                           
      head = ptr;
   }
     
   // then check the rest of the list until we find where it belongs 
   else 
   {
      Node* current = head->next;          // to walk list
      Node* previous = head;               // to walk list, lags behind

      // walk until end of the list or found position to insert
      while (current != NULL && *current->data < *ptr->data) {
            previous = current;                  // walk to next node
            current = current->next;
      }

      // insert new node, link it in
      ptr->next = current; 
      previous->next = ptr; 
   }
   return true;
}//end insert

/***************************** buildList *************************************************
* 
* buildList()
*
*/
template <typename T>
void List<T>::buildList(ifstream& infile) {
   T* ptrData;
   bool successfulRead;                            // read good data
   bool success;                                   // successfully insert
   while(true) {
      
      ptrData = new T();
      
      successfulRead = ptrData->setData(infile);       // fill the NodeData object
      if (infile.eof()) {
         delete ptrData;
         break;
      }

      // insert good data into the list, otherwise ignore it
      if (successfulRead) {
         success = insert(ptrData);
      }
      else {
         delete ptrData;
      }
      if (!success) break;
   }
}

/***************************** makeEmpty *************************************************
* 
* makeEmpty()
*
*/
template <typename T>
void List<T>::makeEmpty()
{
   Node* current,*prev;
	
   current = head;
   while(current != NULL)
   {
	  prev = current;
	  current = current->next;
     delete prev;               
   }
   head=NULL;
}//end makeEmpty

/****************************** intersect ************************************************
*
*
*/
template <typename T>
void List<T>::intersect(const List<T>& listA,const List<T>& listB)
{
   //emtpyList();      //empty current list

   bool done=false;
   Node *tempHead,*current,*currentA,*currentB;
   tempHead=NULL;
   currentA=listA.head;
   currentB=listB.head;

   while(!done)
   {
      //done a list is walked
      if (currentA == NULL || currentB == NULL) {
         done = true;
      //see if ==
      } else if (*currentA->data == *currentB->data) {
         typename List<T>::Node* node = new typename List<T>::Node();
         node->data = currentA->data;

         if (tempHead == NULL) {
            tempHead = node;
            current = node;
         } else {
            current->next = node;
            current = node;
         }
          currentA=currentA->next;        //walk A
          currentB=currentB->next;        //walk B
      } else if (*currentA->data < *currentB->data) {
            currentA=currentA->next;   //walk A closer = B
      } else {
            currentB=currentB->next;   //walk B closer = A
      }

   }
   
   //clean up memory NOTE here due to self intersect self.
   if (!isEmpty())
      this->makeEmpty();

   this->head=tempHead;
}//end intersect

/***************************** merge ************************************************
*
*
*/
template <typename T>
void List<T>::merge(List<T>& listA,List<T>& listB)
{

   bool done=false;
   Node *tempHead,*current,*currentA,*currentB;
   tempHead=NULL;
   currentA=listA.head;
   currentB=listB.head;
   
   while(!done)
   {
      if (currentA == NULL && currentB == NULL) {
         done=true;

      //edge append B
      } else if (currentA == NULL) {
         if (tempHead == NULL) 
            tempHead = currentB;
         else 
            current->next = currentB;
         done=true;
      //edge append A
      } else if (currentB == NULL) {
         if (tempHead == NULL) 
            tempHead = currentA;
         else
            current->next = currentA;
         done=true;
      } else if (*currentA->data < *currentB->data) {
         
            if (tempHead == NULL) {
               tempHead = currentA;
               current = currentA;
            } else {
               current->next = currentA;
               current = currentA;
            }
            currentA=currentA->next;   //walk A
      } else {
            if (tempHead == NULL) {
               tempHead = currentB;
               current = currentB;
            } else {
               current->next = currentB;
               current = currentB;
            }
            currentB=currentB->next;   //walk B
      }

   }//end while
   
   //lists are merged remove pointer to lists
   
   if (this != &listA)
   {
      listA.head = NULL;
   }

   if (this != &listB)
   {
      listB.head = NULL;
   }
   this->head = tempHead;
}//end merge


/********************* operator= **********************************************
**
**
**/
template <typename T>
List<T>& List<T>::operator=(const List<T>& rgtList)
{
   if (this != &rgtList)
   {   
      //empty current list
      if (!isEmpty())
         makeEmpty();   

      this->copyList(rgtList.head,head);
   }
   return *this;
}//end =

/********************* operator== **********************************************
**
**
**/
template <typename T>
bool List<T>::operator==(const List<T>& rgtList) const
{
   bool equal=false;

   if (this == &rgtList)
      true;
   
   Node *currentA = head;
   Node *currentB = rgtList.head;

   while(currentA != NULL && currentB != NULL)
   {
      if (*currentA->data != *currentB->data)
      {
         return false;  //one didn't match 
      }

      currentA = currentA->next;
      currentB = currentB->next;
   }//end while

   if (currentA == NULL && currentB == NULL) //means we reached the end of both
      equal = true;

   return equal; //all matched
   
}//end ==

/********************* operator!= **********************************************
*
*
**/
template <typename T>
bool List<T>::operator!=(const List<T>& rgtList) const
{
   return !(*this == rgtList);
   
}//end !=



/***************************** copyList *************************************************
*  copyList internal method to copy one list head to another list head
*
*/
template <typename T>
void List<T>::copyList(Node* fromNodeHead,Node*& toNodeHead) const {
   Node* current,*newNode,*prevNode;
   current = fromNodeHead;
   
   while(current != NULL) {

      newNode = new Node();
      newNode->data = new T(*current->data);   //copy data pointer

      if (toNodeHead == NULL) {
         toNodeHead = newNode;         //init head
         prevNode = newNode;
      } else {
         prevNode->next = newNode;     //link in
         prevNode = newNode;
      }
      current = current->next;         //walk from list

   }//end while
}//end copyList



template <typename T>
bool List<T>::testDataPointerSame(const List<T>& rgtList) const
{
   bool equal=false;

   if (this == &rgtList)
      true;
   
   Node *currentA = head;
   Node *currentB = rgtList.head;

   while(currentA != NULL || currentB != NULL)
   {
      if (currentA->data != currentB->data)
      {
         return false;  //one didn't match 
      }

      currentA = currentA->next;
      currentB = currentB->next;
   }//end while

   if (currentA == NULL && currentB == NULL) //means we reached the end of both
      equal = true;

   return equal; //all matched
   
}//end testDataPointerSame


template <typename T>
bool List<T>::testNodePointerSame(const List<T>& rgtList) const
{
   bool equal=false;
  
   Node *currentA = head;
   Node *currentB;

   while(currentA != NULL)
   {
      currentB = rgtList.head;

      while(currentB != NULL)
      {
         if (currentA == currentB)
         {
            cout << "same pointer node" << endl;
            cout << currentA << *currentA->data << endl;
            cout << currentB << *currentB->data << endl;
            
            return true;
         }
         currentB = currentB->next;
      }
      currentA = currentA->next;
      
   }//end while

   

   return equal; //all matched
   
}//end testDataPointerSame


#endif


