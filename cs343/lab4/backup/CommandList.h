#ifndef COMMANDLIST_H
#define COMMANDLIST_H

// Notice the forward reference instead of a full blown #include .
// If you only use pointers of another class in a .h file, a forward 
// reference is sufficient. This is a common way to avoid circular includes.

class Command;

// ----- CLASS List ----------------------------------------------------------

class CommandList {
private:
    struct Node {
       Command* cmd;                              // pointer to the data 
       Node* next;                                   
    };
    Node *head, *tail;

public:
    CommandList();
    ~CommandList();
    void add(Command*);
    void printList();
};
                
#endif


