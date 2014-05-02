//************************************************************************************
#ifndef ItemTree_H
#define ItemTree_H

#include "Item.h"

class ItemTree 
{

private:
	struct Node
	{					    
		Item* data;
		Node* right;
		Node* left;
	};
	Node* root;                         // root of the tree

public:
	ItemTree();
	~ItemTree();
	//void buildTree(ifstream&);
	// insert object into the tree, parameter holds pointer to object to insert
	bool insert(Item*);
	// retrieve object, first parameter is object to retrieve
	// second parameter holds pointer to found object, NULL if not found
  bool find(const string&,Item*&) const;
	bool retrieve(const Item& , Item*&) const; //retrieves a movie in tree
	bool findHelper(const Item&,Node *,Item *&) const;
	bool findHelper(const string&,Node *,Item *&) const;
	
	void display() const;			    //displays the contents of a tree
	void displayHelper(Node*) const;    //helps display()
	void makeEmpty();				    //empties the current tree
	void makeEmptyHelper(Node*);        //helps makeEmpty()
	bool isEmpty() const;			    //returns true if tree is empty

};

#endif


