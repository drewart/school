//graphm.h  Drew Pierce (drpier)
#ifndef GRAPHM_H
#define GRAPHM_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <climits>
#include "nodedata.h"

//#define DEBUG   //uncomment for debug output

const int MAXNODES = 101;

//--------------------------------------------------------------------------------
// // GraphM is a class that stores a graph.
//         GraphM is able to calculate Dijkstra's shortest path algorithm
//
//
// GraphM *graph = new GraphM()
// graph->buildGraph(infile);    -- builds nodes from a file stream
// graph->displayAll()  displays all nodes
// 
// Warning:
//    No copy constructor
//
// Asummptions:
//    No path/edge weight is negative 
//    
//
//

//helper struct for string 
struct TableType
{
   bool visited;
   int dist;
   int path;
};

// GraphM class
class GraphM 
{

public:
  GraphM();
  ~GraphM();
  void buildGraph(ifstream&);
  void findShortestPath();
  void displayAll() const;
  void display(int,int) const;
  void insertEdge(int,int,int);
  void debug();

private:

  NodeData *data;		     // data for graph nodes information
  //NodeData *data[MAXNODES];      // data for graph nodes information
  
  int size;                         // number of nodes in the graph
  
  TableType T[MAXNODES][MAXNODES];    // stores visited, distance, path

  bool findSmallestNotVisited(int,int&) const;   //gets non visited node

  void markVisitied(int,int);
  void getPathHelper(int,int,int[]) const;

};


#endif


