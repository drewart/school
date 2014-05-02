#include "BSTree.h"


BSTree::BSTree()
{
   root=NULL;
}

BSTree::~BSTree()
{
   makeEmpty();
}

bool BSTree::insert(Client *dataptr) 
{
   Node* ptr = new Node;
   if (ptr == NULL) return false;            // out of memory
   ptr->data = dataptr;
   ptr->left = ptr->right = NULL;
   if (isEmpty()) 
   {
      root = ptr;
   }
   else 
   {
      Node* current = root;                           // walking pointer
      bool inserted = false;                          // whether inserted yet

      // if item is less than current item, insert in left subtree,
      // otherwise insert in right subtree
      while (!inserted) 
      {
         if (*ptr->data < *current->data) {
            if (current->left == NULL) {              // insert left
               current->left = ptr;
               inserted = true;
            }
            else
               current = current->left;               // one step left
         }
         else {
            if (current->right == NULL) {             // insert right
               current->right = ptr;
               inserted = true;
            }
            else
               current = current->right;              // one step right
         }
      }//end while

   }//end else
   return true;
}//end insert

//
bool BSTree::isEmpty() const
{
   return (root == NULL);
}

// 
//NOTE: no UPPER or LOWER bound check
bool BSTree::retrieve(Client* client,Client *& foundClient) const
{
   foundClient=NULL;
   if (isEmpty())
      return false;

   return findHelper(client->id,root,foundClient);
}

//NOTE: input bad id,negitive
bool BSTree::find(int id,Client *&client) const
{
   client=NULL;      //in case not found
   if (isEmpty())
      return false;

   return findHelper(id,root,client);
}//end find


//findHelper
// note null check done in 
bool BSTree::findHelper(int id,Node *node,Client *&client) const
{
   bool found = false;

   if (id == node->data->id) 
   {
      client=node->data;         //set found client
      found = true;
   } 
   else if (id < node->data->id && node->left != NULL)
      found = findHelper(id,node->left,client);
   else if (node->right != NULL) 
      found = findHelper(id,node->right,client);
   
   return found;
}

void BSTree::display() const
{
   if (!isEmpty())
      displayHelper(root);
}

//print sorted Binary Tree
void BSTree::displayHelper(Node* node) const
{

   if (node->left != NULL)
      displayHelper(node->left);

   cout << *node->data << endl;
   
   if (node->right != NULL)
      displayHelper(node->right);
   
}


void BSTree::makeEmpty()
{
   if (!isEmpty())
      clearTreeHelper(root);
   root = NULL;
}


void BSTree::clearTreeHelper(Node* node)
{
   Node* left = node->left;
   Node* right = node->right;
   Client* data = node->data;
   delete data;
   delete node;

   if (left != NULL)
      clearTreeHelper(left);

   if (right != NULL)
      clearTreeHelper(right);
   
}
