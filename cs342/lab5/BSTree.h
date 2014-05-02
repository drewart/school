//Client data contains unique account number

#ifndef BSTREE_H
#define BSTREE_H

//#include "nodedata.h"
#include <iostream>
#include <fstream>
#include "client.h"
using namespace std;

class BSTree 
{

public:
   BSTree();
   ~BSTree();

   bool insert(Client*);         //insert client
   bool retrieve(Client*,Client*&) const; //find client by account
   bool find(int,Client*&) const;       //find client by account
   bool isEmpty() const;               //check if empty
   void display() const;
   void makeEmpty();
   

private:
   struct Node 
   {
      Client* data;           // pointer to actual data stored
      Node* left;               // pointer to left child Node, left subtree
      Node* right;              // pointer to right child Node, right subtree
   };
   bool findHelper(int,Node*,Client*&) const;
   void clearTreeHelper(Node* n);
   Node* root;
   void displayHelper(Node*) const;
};



#endif
