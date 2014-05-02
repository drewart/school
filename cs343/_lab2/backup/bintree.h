// B-Tree class

#ifndef BINTREE_H
#define BINTREE_H
#include <iostream>
#include "nodedata.h"
using namespace std;

//typedef char * NodeData;



struct Node
{
  NodeData* data;
  Node* left;
  Node* right;
};

class BinTree 
{


public:
  friend ostream& operator<<(ostream& output, const BinTree&);  
  BinTree();
  BinTree(const BinTree &);
  ~BinTree();
  bool isEmpty() const;
  void makeEmpty();

  bool insert(NodeData*);
  bool retrieve(NodeData,NodeData*&) const;

  BinTree& operator=(const BinTree &);
  bool operator==(const BinTree &) const;
  bool operator!=(const BinTree &) const;

  void displaySideways() const;

  //print 
  void printTree() const;
  void printTree(ostream&,Node*) const;
  void printTreeHelper(Node*,int) const;
  void printTreeLevel(Node*,int,int) const;
  int getDepth(const NodeData&) const;
  int getMaxDepth() const;

  void bstreeToArray(NodeData*[]);
  void arrayToBSTree(NodeData*[]);

  void copy(const BinTree&,BinTree*&) const;

private:
  Node* root;

  //utility functions
  void inorderHelper() const;
  void sideways(Node*,int) const;  //provided,helper for displaySideways();
  bool findHelper(Node*,NodeData&,NodeData*&) const;
  int getNodeDataDepthHelper(const NodeData&,  Node*,int) const;
  void getDepthHelper(Node*,int,int&) const;
void makeEmptyHelper(Node*);
  bool equalHelper(Node*,Node*) const;
  void copyNodes(const Node*,Node*&) const;
  void bstreeToArrayHelper(NodeData *[],int&,Node*);
  void arrayToBSTreeHelper(NodeData*[],Node*&,int,int);

    
};


#endif

