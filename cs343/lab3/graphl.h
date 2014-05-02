//graphl.h  Drew Pierce (drpier)
#ifndef GRAPHL_H
#define GRAPHL_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <climits>
#include "nodedata.h"

//#define DEBUG   //uncomment for debug output

//--------------------------------------------------------------------------------
//
//  GraphL class that stores a graph and prints a depth search first of the nodes
//     
//
//  Example:
//    GraphL G;
//    G.buildGraph(infile);
//    G.displayGraph();
//    G.depthFirstSearch();
//
//  Warnings:
//    No copy constructor
//
// Assumptions:
//      Data file has no more than 100 nodes (GRAPH_MAX_NODES)
//      Using head first for depth search
//      Assuming correct formated data
//      Search is based on data file order
//      formating output of spaces is not critical



const int GRAPH_MAX_NODES = 101;      //max # nodes

//helper struct

struct EdgeNode;            //forward reference for the compiler
struct GraphNode            //strucs used for simplicity, use classes if desired
{
   EdgeNode* edgeHead;      //head of the list of edges
   int index;               //subscript of the node
   NodeData *data;          //pointer to NodeData
   bool visited;            //bool for depth search
};

//edge node
struct EdgeNode {
  int adjGraphNode;           //subscript of the adjacent graph node
  EdgeNode* nextEdge;
};


class GraphL 
{

public:
  GraphL();       //constructor
  //GraphL(GraphL)  //not implemented
  ~GraphL();      //destruct

  //build graph
  void buildGraph(ifstream&);

  //output methods
  void displayGraph() const;      //display
  void depthFirstSearch();        //search depth


private:
  int size;         //size of nodes
  
  GraphNode nodes[GRAPH_MAX_NODES];   //holds nodes

  void insertEdge(int,int);

  //search helpers
  void depthFirstSearchHelper(GraphNode&);
  void markAllNotVisitied();                

};


#endif

