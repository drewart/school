//graphl.cpp  Drew Pierce (drpier)
#include "graphl.h"

#pragma region constructor/descrutor {{{
//------------------------------------------------------------------------------
//  GraphL constructor
//  see header file for details
//
//
GraphL::GraphL()
{
  //
  size = 0;

}

//------------------------------------------------------------------------------
// GraphL ~GraphL
// 
// clean up memory 
//
GraphL::~GraphL()
{
  //clean edgenodes
  for(int i = 1; i <= size; i++)
  {
  
    //clean up data
    delete nodes[i].data;

    //clean up edges
    if (nodes[i].edgeHead != NULL)
    {
        EdgeNode *current = nodes[i].edgeHead;

        //loop through nodes to clean
        while(current != NULL)
        {
          EdgeNode *prev = current;
          current = current->nextEdge;
          delete prev;
          prev = NULL;
        }
       
    }//end if
  
  }//end for

}//end ~GraphL

#pragma endregion }}}

#pragma region object builders methods {{{
//------------------------------------------------------------------------------
//  buildGraph  builds a graph from txt file
//
//
//
void GraphL::buildGraph(ifstream &stream)
{
   //read size
   stream >> size;

   //check eof
   if (stream.eof())
      return;

   //size check
   if (size <= 0 || size >= GRAPH_MAX_NODES)
      return;
   NodeData *temp;
   
   //eat white space after size
   string dumb;
   getline(stream,dumb);

   if (stream.eof())
      return;

   //read node data
   for(int i = 1; i < size+1; i++) 
   {
      //create new node
      temp = new NodeData();
      //set data
      if (!temp->setData(stream))
      {
        //clean up bad sets
         delete temp;
         break;
      }

      //set node data
      nodes[i].index = i;
      nodes[i].data = temp;
      nodes[i].edgeHead = NULL;
      
#ifdef DEBUG
     cout << "adding Node = " << *nodes[i]->data << endl;
#endif
   }//end for size

   if (stream.eof())
     return;

   int nodeA = 0;
   int nodeB = 0;

   do
   {
      stream >> nodeA;
      stream >> nodeB;
#ifdef DEBUG
      cout << "node A " << nodeA 
        << " nodeB " << nodeB << endl;
#endif
    if (nodeA == 0 && nodeB == 0)
       break;

    this->insertEdge(nodeA,nodeB);

   } while(!stream.eof());


}//end buildGraph


//--------------------------------------------------------------------------------
// insertEdge
//  inserts edge into the graph edgeHead list
//  NOTE: inserting edge nodes at the begining of list
//
//
void GraphL::insertEdge(int nodeA,int nodeB)
{

#ifdef DEBUG
   cout << "insertEdge from: " << nodeA << " to: " << nodeB << endl;
#endif

   //create edge node and find where to insert into GraphNode
   EdgeNode *newEdge = new EdgeNode();
   newEdge->adjGraphNode = nodeB;
   newEdge->nextEdge = NULL;

  if (nodes[nodeA].edgeHead == NULL)
  {
    nodes[nodeA].edgeHead = newEdge;
  }
  else 
  {
    //insert newNode at head, NOTE: may not need 'if' above
    EdgeNode *oldHead = nodes[nodeA].edgeHead;  //backup head
    newEdge->nextEdge = oldHead;                //rewire new to point to head
    nodes[nodeA].edgeHead = newEdge;            //new head

    //or insert at end
    //while(current->nextEdge != NULL)
    //{
    //    current = current->nextEdge; 
    //}
    //current->nextEdge = newEdge;
  }

}//end insertEdge


#pragma endregion object builder }}}


#pragma region search {{{

//---------------------------------------------------------------------------------
// depthFirstSearch
//
//
void GraphL::depthFirstSearch()
{
  //mark nodes as not visited
  markAllNotVisitied(); 
  cout << "Depth-first ordering:\t";
  //for 1 .. n nodes
  for(int i = 1; i <= size; i++)
  {
    //check if not visited
    if (!nodes[i].visited) 
      depthFirstSearchHelper(nodes[i]);
  
  }
  cout << endl;
}

//---------------------------------------------------------------------------------
// depthFirstSearchHelper
//   help method for depth first search
//
//
void GraphL::depthFirstSearchHelper(GraphNode &node)
{
  //mark node visited so it doesn't get hit again
  node.visited = true;
  cout << " " << node.index;
  EdgeNode *edge  = node.edgeHead;
  //loop edges
  while (edge != NULL)
  {
    int idx = edge->adjGraphNode;

    //search sub nodes that are not visited
    if (!nodes[idx].visited)
      depthFirstSearchHelper(nodes[idx]);
    edge = edge->nextEdge;
  }
}

//---------------------------------------------------------------------------------
// markAllNotVisitied
//   marks all nodes not visitied
//
void GraphL::markAllNotVisitied() 
{

  for(int i = 1; i <= size; i++)
  {
    nodes[i].visited = false;
  }
}


#pragma endregion search }}}


#pragma region display {{{

//------------------------------------------------------------------------------
//
//  displayGraph 
//    displays the content of the graph object
//
void GraphL::displayGraph() const
{
  cout << "Graph:" << endl;

  for(int i = 1; i <= size; i++)
  {
  
    cout << "Node " << i << "\t\t" << *nodes[i].data << endl;

    EdgeNode *current = nodes[i].edgeHead;

    //print edges
    while(current != NULL)
    {
      cout << "  edge " << i;
      cout << setw(4) << current->adjGraphNode << endl;
      current = current->nextEdge;
    }
    

  }//end for size
}//end displayGraph

#pragma endregion display methods }}}

