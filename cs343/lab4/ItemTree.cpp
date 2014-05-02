#include "ItemTree.h"

//{{{ItemTree
ItemTree::ItemTree()
{
   root = NULL;
}
//}}}

//{{{~ItemTree
ItemTree::~ItemTree()
{
  //cout << "~ItemTree()" << endl;
   makeEmpty();
}
//}}}

//{{{insert
bool ItemTree::insert(Item* item) 
{
    Node* ptr = new Node;
   if (ptr == NULL) return false;            // out of memory
   ptr->data = item;
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
         if (*ptr->data == *current->data)
           return false;
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
}
//}}}insert

//{{{retrieve
bool ItemTree::retrieve(const Item& search, Item*& foundItem) const
{
      foundItem=NULL;
      if (isEmpty())
      return false;

   return findHelper(search,root,foundItem);
}
//}}}

//{{{retrieve
bool ItemTree::find(const string& key, Item*& foundItem) const
{
      foundItem=NULL;
      if (isEmpty())
      return false;

   return findHelper(key,root,foundItem);
}
//}}}

//{{{findHelper
bool ItemTree::findHelper(const Item& findItem,Node *node,Item *&foundItem) const
{
   if (node == NULL)
      return false;
   
   bool found = false;

   int result = findItem.compareTo(node->data);
   if (result == 0) 
   {
      foundItem=node->data;         //set found 
      found = true;
   } 
   else if (result < 0)
     found = findHelper(findItem,node->left,foundItem);
   else if (!found)
     found = findHelper(findItem,node->right,foundItem);
   
   return found;
}//findHelper
//}}}

//{{{findHelper
bool ItemTree::findHelper(const string& key,Node *node,Item *&foundItem) const
{
   if (node == NULL)
      return false;
   
   bool found = false;

   if (key == node->data->getSortString()) 
   {
      foundItem=node->data;         //set found 
      found = true;
   } 
   else if (key < node->data->getSortString())
     found = findHelper(key,node->left,foundItem);
   else if (!found)
     found = findHelper(key,node->right,foundItem);
   
   return found;
}//findHelper
//}}}

//{{{display
void ItemTree::display() const

{
   if (!isEmpty())
   displayHelper(root);

}//display()
//}}}

//{{{displayHelper
void ItemTree::displayHelper(Node* node) const    //helps display()
{
   if (node == NULL)
      return;
   
   displayHelper(node->left);

   cout << *node->data << endl;
   
   displayHelper(node->right);

}//end displayHelper
//}}}

//{{{makeEmpty
void ItemTree::makeEmpty()
{
   if (!isEmpty())
      makeEmptyHelper(root);
   root = NULL;
}//end makeEmpty()
//}}}

//{{{makeEmptyHelper
void ItemTree::makeEmptyHelper(Node* node)
{
	Node* left = node->left;
   Node* right = node->right;
   Item* data = node->data;
   
   //delete data;
   delete node;

   if (left != NULL)
      makeEmptyHelper(left);

   if (right != NULL)
      makeEmptyHelper(right);
}//end makeEmptyHelper()
//}}}

//{{{isEmpty()
bool ItemTree::isEmpty() const
{
   return (root == NULL);
}//end isEmpty()
//}}}

