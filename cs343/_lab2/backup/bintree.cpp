#include "bintree.h"

/******************************* << *******************************************  
* display NodeData object
*/
ostream& operator<<(ostream& output, const BinTree& tree) { 

   tree.printTree(output,tree.root);
   output << endl;
   return output;
}

#pragma region construtors/descrutors
/******************************************************************************
* BinTree() constructor
*
*/
BinTree::BinTree()
{
  root = NULL;
}


/******************************************************************************
* BinTree() constructor
*
*/
BinTree::BinTree(const BinTree &tree)
{
  if (!isEmpty())
    makeEmpty();

  //copy nodes
  this->copyNodes(tree.root,this->root);
}


/******************************************************************************
* BinTree() constructor
*
*/
BinTree::~BinTree()
{
  makeEmpty();
}
#pragma endregion 

#pragma region empty check and clean
/******************************************************************************
* isEmpty() returns bool if the tree is empty
*
*/
bool BinTree::isEmpty() const
{
  return (this->root == NULL);
}

void BinTree::makeEmpty()
{
 if (!isEmpty())
      makeEmptyHelper(root);
}

void BinTree::makeEmptyHelper(Node *node)
{
   if (node != NULL)
     return;

   //clean left 
  makeEmptyHelper(node->left);

  //clean right
  makeEmptyHelper(node->right);

  //clean up
  node->data = NULL;
  delete node->data; 

  node=NULL;
  delete node;
}
#pragma endregion

#pragma region operator overload
//=
BinTree& BinTree::operator=(const BinTree &tree)
{
  if (this != &tree)
  {
     this->makeEmpty();
     copyNodes(tree.root,this->root);
  }
  return *this;
}

//==
bool BinTree::operator==(const BinTree &bTree) const
{
  return equalHelper(root,bTree.root);
}


/// equalHelper
///
bool BinTree::equalHelper(Node *left,Node *right) const
{
  //base case nodes are null
  if (left == NULL && right == NULL)
    return true;
  else if (left == NULL && right != NULL)
    return false;
  else if (left != NULL && right == NULL)
    return false;
  else 
  {
    //check if current node is equal
    //and check if sub-tree nodes are equal
    if (*left->data == *right->data && 
        equalHelper(left->left,right->left) && 
           equalHelper(left->right,right->right))
    {
        return true;
    }
    else
      return false;
  }
}

//!=
bool BinTree::operator!=(const BinTree &bTree) const
{
  return !(equalHelper(root,bTree.root));
}
#pragma endregion

 
/******************** insert ***************************************************
* insert
*
*/
bool BinTree::insert(NodeData* data)
{
  Node* node = new Node;
  
  if (node == NULL) return false;            // out of memory

   node->data = data;
   node->left = node->right = NULL;
   if (isEmpty()) 
   {
      root = node;
   }
   else 
   {
      Node* current = root;                           // walking pointer
      bool inserted = false;                          // whether inserted yet

      // if item is less than current item, insert in left subtree,
      // otherwise insert in right subtree
      while (!inserted) 
      {
        //duplicate check
        if (*node->data == *current->data)
        {
          inserted = true;
        }
        else if (*node->data < *current->data)
        {
            if (current->left == NULL) {              // insert left
               current->left = node;
               inserted = true;
            }
            else
               current = current->left;               // one step left
         }
         else 
         {
            if (current->right == NULL) {             // insert right
               current->right = node;
               inserted = true;
            }
            else
               current = current->right;              // one step right
         }
      }//end while

   }//end else
   return true;
}

#pragma region retrieve
//retrieve recieves a NodeData item from the tree
bool BinTree::retrieve(NodeData findData,NodeData*& foundData) const
{
   foundData=NULL;
   if (isEmpty())
      return false;

   return findHelper(root,findData,foundData);
}

///findHelper searches for NodeData in B-Tree
bool BinTree::findHelper(Node *current,NodeData &findData,NodeData *&foundData) const
{
    bool found = false;

   if (findData == *current->data) 
   {
      foundData = current->data;         //set found data
      found = true;
   } 
   //search left
   else if (findData < *current->data && current->left != NULL)
      found = findHelper(current->left,findData,foundData);
   //search right
   else if (current->right != NULL) 
      found = findHelper(current->right,findData,foundData);
   
   return found; 
}
#pragma endregion


#pragma region print/dispaly
//-----------------------------------------------------------------------------
// printTree 
// displays a inorder tree
// 

void BinTree::printTree(ostream& output,Node* node) const
{
  if (node == NULL)
    return;

   printTree(output,node->left);

   output << *node->data << " ";
   
   printTree(output,node->right);
}

void BinTree::inorderHelper() const
{

}


//---------------------------------------------------------------------------
// displaySideways 
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.

void BinTree::displaySideways() const 
{
   sideways(root, 0);
}

void BinTree::sideways(Node* current, int level) const 
{
   if (current != NULL) {
      level++;
      sideways(current->right, level);

      // indent for readability, 4 spaces per depth level 
      for(int i = level; i >= 0; i--) {
          cout << "    ";
      }

      cout << *current->data << endl;        // display information of object
      sideways(current->left, level);
   }
}

void BinTree::printTree() const
{
   printTreeHelper(root,0); 
}

void BinTree::printTreeHelper(Node *node,int level) const
{

  if (node == NULL)
    return;
  printTreeHelper(node->left,level+1);
   
  cout << *node->data << endl;

  printTreeHelper(node->right,level+1);

}
#pragma endregion

#pragma region depth methods
int BinTree::getDepth(const NodeData &nodeData) const
{
    return getNodeDataDepthHelper(nodeData,this->root,1);
}

int BinTree::getNodeDataDepthHelper(const NodeData &findNodeData,Node* node,int depth) const
{
  int found = 0;
  if (node == NULL)
    return found;

    if (*node->data == findNodeData)
      found = depth;
    else
    {
      found = getNodeDataDepthHelper(findNodeData,node->left,depth+1);

      if (found == 0)
        found = getNodeDataDepthHelper(findNodeData,node->right,depth+1);
    }

    return found;
}//getNodeDataDepthHelper

int BinTree::getMaxDepth() const
{
  int max = 0;
  getDepthHelper(root,1,max);
  return max;
}//getMaxDepth()

void BinTree::getDepthHelper(Node* node,int level,int &max) const
{
  if (level > max)
    max = level;
  if (node==NULL)
    return;
  else if (node->left != NULL)
    getDepthHelper(node->left,level+1,max);
  else if (node->right != NULL)
    getDepthHelper(node->left,level+1,max);

}//end getDepthHelper

#pragma endregion 





//
void BinTree::printTreeLevel(Node *node,int level,int printLevel) const
{
  if (node == NULL)
    return;
  else if (level == printLevel)
  {
    cout << *node->data << "\t";
  }
  else if (node->left != NULL)
    printTreeLevel(node->left,level+1,printLevel);
  else if (node->right != NULL)
    printTreeLevel(node->left,level+1,printLevel);

}


#pragma region Util copy functions

//public copy 
void BinTree::copy(const BinTree& tree,BinTree *&copy) const
{
  //do nothing check
  if (tree.isEmpty())
    return;

  //clean old
  if (copy->root != NULL)
    copy->makeEmpty();

  copyNodes(tree.root,copy->root); 
}

// private copyNode Helper
void BinTree::copyNodes(const Node* orig,Node*& copy) const
{
  //do nothing check
  if (orig == NULL)
    return;   

  copy = new Node();
  copy->left = NULL;
  copy->right = NULL;

  //init new NodeData
  copy->data = new NodeData(*orig->data);
  //copy left
  copyNodes(orig->left,copy->left);
  //copy right
  copyNodes(orig->right,copy->right);
   
}

#pragma endregion 

#pragma region tree & array methods

void BinTree::bstreeToArray(NodeData* ndArray[])
{
  int index = 0;
  bstreeToArrayHelper(ndArray,index,root);
  root = NULL;
  
}

/**************************************************************************
* bstreeToArrayHelper
*
*/
void BinTree::bstreeToArrayHelper(NodeData *ndArray[],int &index,Node* node)
{
  if (node == NULL)
    return;

  bstreeToArrayHelper(ndArray,index,node->left);
  ndArray[index] = node->data;
  index++;
  //clear pointer to NodeData
  node->data = NULL;

  bstreeToArrayHelper(ndArray,index,node->right);

  //clean up node
  delete node;
}


//-----------------------------------------------------------------------------
// arrayToBSTree 
//
//
void BinTree::arrayToBSTree(NodeData* ndArray[])
{
  //clear array
  makeEmpty();

  //find array length searching for first null
  int length = -1;
  while(length < 100)
  {
    if (ndArray[length+1] == NULL)
      break;                        //found array length
     length++;
  }
      
  //call helper to fill tree
  if (length > 0)
    arrayToBSTreeHelper(ndArray,this->root,0,length);
}


void BinTree::arrayToBSTreeHelper(NodeData* ndArray[],Node *&node,int low,int high)
{
  //get the root node for the array
  //using half way point to set root
  int index = (high + low) / 2;
  //cout << "index:" << index << endl;
  if (ndArray[index] == NULL)
    return;
  
   
   node = new Node();
   node->data = ndArray[index];
   node->left = NULL;         //default to NULL
   node->right = NULL;        //default to NULL

   ndArray[index] = NULL;   //reset pointer

   //insert left with new low and high
   if (low != index)
     arrayToBSTreeHelper(ndArray,node->left,low,index);
   //insert right
   if (index != high)
     arrayToBSTreeHelper(ndArray,node->right,index+1,high);
  

}
#pragma endregion
