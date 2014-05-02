
//LinkList template

#ifndef LINKLIST_H
#define LINKLIST_H
#include <iostream>
using namespace std;

template <class T>
class Node 
{
	
public:
	//
	Node(T* pData) 
	{
		item = pData;
	}
	//copy constructor
	Node(const Node<T>& N) {
		item = N.item;
		previous = NULL;
		next = NULL;
	} 
	
	T* item;
		
	Node<T> *previous;
	Node<T> *next;
};



template <class T>
class LinkList
{

public:
	LinkList() : Count(0) { HEAD=TAIL=NULL; } 
	~LinkList();
	
	void Add(T* pData)
	{
		if (Count==0)
		{
			HEAD = new Node<T>(pData);
			HEAD->previous=NULL;
			TAIL=HEAD;
		}
		else
		{
			Node<T> *current = new Node<T>(pData);    //new Type node
			TAIL->next=current; 
			current->previous=TAIL;                   //point new previous to last node
			TAIL=current;                             //point tail to new node 
			current->next=NULL;                       //point next to null
		}
		Count++;
	};

	void print()
	{
		Node<T> *cur = HEAD;
		while(cur != NULL)
		{
			cout << *cur->item;
			cout << endl;
			cur = cur->next;
		}
	
	}

	int Count;

	class iterator;
	friend class iterator;
	class iterator {
		//LinkList<T> *list
		Node<T> *c;
	public:
		iterator(const LinkList<T>& l) : c(l.HEAD) { index = -1;};
		//copy constructor;
		iterator(const iterator& t1) : c(t1.c) { index = t1.index;  };
		int index;
		bool MoveNext() 
		{ 
			bool moveNext=false;
			index++;
			//HEAD pointer
			if (index == 0 && c != NULL)
			{
				moveNext=true;
			}
			else if(c->next != NULL)
			{
				c = c->next;
				moveNext= true;
			}
			else 
			{
				moveNext= false;
			}
			return moveNext;
		}

		T item() const 
		{
			return *c->item;
		}

      /*T* item() const 
		{
			if(!c) return 0;
			return c->item;
		}*/

		T operator->() const 
		{
			if (c != NULL)
			return *item();
		}

		T operator*() const { return item(); }




	};//end iterator
private:
   void makeEmpty();

   Node<T> *HEAD;
	Node<T> *TAIL;

};

template <class T>
LinkList<T>::~LinkList()
{
   makeEmpty();
}

template <class T>
void LinkList<T>::makeEmpty()
{
   Node<T>* current,*prev;
	
   current = HEAD;
   while(current != NULL)
   {
	  prev = current;
	  current = current->next;
     delete prev->item;          //Note deleting pointer to data
     prev->item = NULL;
     delete prev;               
     prev = NULL;
   }

   HEAD=TAIL=NULL;
}

#endif
