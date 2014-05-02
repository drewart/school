//graphm.h  Drew Pierce (drpier)
#ifndef GRAPHM_H
#define GRAPHM_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <climits>
#include "nodedata.h"

//#define DEBUG   //uncomment for debug output

//max nodes
const int MAXNODES = 101;

//--------------------------------------------------------------------------------
//
// GraphM is a class that stores a graph.
//      GraphM is able to calculate  Dijkstra's shortest path
//      display shortest path from node to node (if possible)
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
//    Formating output of spaces is not critical
//    
//

//helper struct for string 
struct TableType
{
   bool visited;
   int dist;
   int path;
};

// GraphM class see above for details
class GraphM 
{

public:
  GraphM();
  ~GraphM();

  //builder methods
  void buildGraph(ifstream&);
  void insertEdge(int,int,int);
  void findShortestPath();

  //display methods
  void displayAll() const;        //displays all nodes and paths
  void display(int,int) const;    //displays

  //NOTE remove in production
  void debug();                   //personal debug method 

private:

  //data members
  NodeData data[MAXNODES];      // data for graph nodes information
  int C[MAXNODES][MAXNODES];     // cost array , the adjacenty matrix
  
  int size;                         // number of nodes in the graph
  
  TableType T[MAXNODES][MAXNODES];    // stores visited, distance, path

  //helper methods
  bool findSmallestNotVisited(int,int&) const;   //gets non visited node
  void markVisitied(int,int);
  void getPathHelper(int,int,int[]) const;    //gets array of path

};


#endif


