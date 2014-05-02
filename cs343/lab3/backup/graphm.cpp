//graphm.cpp Drew Pierce (drpier)
#include "graphm.h"

#pragma region Contstructors {{{
//-----------------------------------------------------------------------------
// GraphM()
// constructor
//
GraphM::GraphM()
{
#ifdef DEBUG
   cout << "in constructor" << endl;
#endif

   size=0;
   for(int i = 0; i < MAXNODES; i++)
   {
      data[i] = NULL;
      for(int j = 0; j < MAXNODES; j++)
      {
         C[i][j] = -1;   //note using -1 for no edge
         TableType t;
         t.visited = false;
         t.dist = INT_MAX;
         t.path = 0;
         T[i][j] = t;
      }
   }
   //init array
}

//-----------------------------------------------------------------------------
// ~GraphM()
// descructor
//
GraphM::~GraphM()
{
   //
   size=0;
   for(int i = 1; i <= size; i++)
   {
     delete data[i];
     data[i] = NULL;
     /*for(int j = 1; i <= size; i++)
     {
     }*/
   }
}

#pragma endregion constructors }}}

#pragma region object builders {{{

//-----------------------------------------------------------------------------
// insertEdge
//
//
void GraphM::insertEdge(int nodeA,int nodeB,int weight)
{
   //insert path in matrix
   C[nodeA][nodeB] = weight;
}

//-----------------------------------------------------------------------------
// buildGraph
// builds a graph object from input data file
//
//
void GraphM::buildGraph(ifstream &stream)
{
   //read size
   stream >> size;

   //check eof
   if (stream.eof())
      return;

   //size check
   if (size <= 0 || size >= MAXNODES)
      return;
   
   NodeData *temp;
   
   //eat size white space
   string dumb;
   getline(stream,dumb);

   if (stream.eof())
      return;

   data = new NodeData[size];

   //read node strings
   for(int i = 1; i < size+1; i++ )
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

      //add to data
      data[i] = temp;

#ifdef DEBUG
     cout << "adding Node = " << *data[i] << endl;
#endif

   }//end for

   if (stream.eof())
      return;

   int nodeA,nodeB,weight;

   //read edges & paths
   do
   {
      stream >> nodeA;
      stream >> nodeB;
      stream >> weight;
#ifdef DEBUG
      cout << "node A " << nodeA 
        << " nodeB " << nodeB << " Weight " << weight << endl;
#endif
      if (nodeA == 0 && nodeB == 0 && weight == 0)
         break;
      this->insertEdge(nodeA,nodeB,weight);

   } while(!stream.eof());

   stream.ignore(1);		//skip \n

}//end buildGraph

#pragma endregion builder }}}


#pragma region findShortestPath {{{ 

//-----------------------------------------------------------------------------

void GraphM::findShortestPath()
{
  //size check
  if (size <= 0)
    return;


#ifdef DEBUG
   cout << "findShortestPath" << endl;
#endif
   for(int source=1; source <= size; source++)
   {
#ifdef DEBUG
     cout << "**source:**" << source << endl;
#endif
     T[source][source].dist = 0;

     //find the shortest distance from source to all other nodes
     for ( int i = 1; i < size; i++)
     {
       int v;   //vertex 
       //find v - unvisited node smallest
       //find smallest non-visited node
       if (findSmallestNotVisited(source,v))
       {
         markVisitied(source,v);

#ifdef DEBUG
            cout << "v:" << v << endl;
#endif

         for(int w = 1; w <= size; w++)
         {
            //if not adjacent
            if (C[v][w] == -1) 
              continue;
#ifdef DEBUG
            cout << "\tw:" << w << endl;
#endif

#ifdef DEBUG
    cout << "\tT[source][w]" << ((T[source][w].visited) ? "W visited" : "W not visited") << endl;
#endif
           //w not visited skip
           if (T[source][w].visited == true)
             continue;    //skip

           //NEED TO TEST not sure if right place
           /*if (T[source][v].dist == INT_MAX && C[source][v] >= 0) 
           {
              T[source][v].dist = C[source][v]; 
           }*/

           // get connection dist
           int dist = T[source][v].dist + C[v][w];

#ifdef DEBUG
            cout << "\tcurrent v to w :" << T[source][w].dist << endl;
            cout << "\tsource + v + d dist :" << dist << endl; 
#endif

           //comapre min of source + v + d to source -> w
           if (dist < T[source][w].dist)
           {

#ifdef DEBUG
                cout << "\t\tbetter dist: " << dist << endl;
                cout << "\t\tpath : " << v << " " <<  w << endl;
#endif
                //new dist/weight from source to Node W
                T[source][w].dist = dist;
                //new path to W
                T[source][w].path = v;
           }//end if

         }//for w
       
       }//end find smallest v
     
     }//end for i


   }//end source for
}

//-----------------------------------------------------------------------------
// 
// findSmallestNotVisited
//    finds the smallest V that is not visited
//   note weight can not be 0
//
bool GraphM::findSmallestNotVisited(int source,int &target) const
{

#ifdef DEBUG
   cout << "  in find smallest dist" << endl;
#endif 

   bool found = false;
   int smallest = INT_MAX;
   target = 0;
   
	for(int i=1; i<=size; i++)
	{

     //current weight from T
    int weight = T[source][i].dist;
#ifdef DEBUG
      cout << "\t\t\ti:" << i << endl;
      cout << "\t\t\tC[source][i]:" << weight << endl;
#endif 
	   
	   
	   if (T[source][i].visited == false 
	      && weight >= 0 && weight < smallest)
	   {

	       smallest = weight;
	       target = i;
         found = true;
      #ifdef DEBUG
         cout << "\t\t\tfound smallest i:" << i << endl;
         cout << "\t\t\t\tsmallest:" << smallest << endl;
       #endif
	   }
#ifdef DEBUG
     cout << ((T[source][i].visited) ? "\t\t\t visited" : "\t\t\tnot visited") << endl;
#endif
	}//end
	
	return found;
}//end findSmallestNotVisited

//-----------------------------------------------------------------------------
//
//
//
//
void GraphM::markVisitied(int source,int target)
{
#ifdef DEBUG
    cout << "\t\tmarking " << source << "," << target << " visited" << endl; 
#endif

    T[source][target].visited = true;
#ifdef DEBUG
    cout << "\t\t" << T[source][target].visited << endl;
#endif
}

#pragma endregion }}}



#pragma region display {{{

//-----------------------------------------------------------------------------
// display
//  displays shortest path from source node to target node
//
void GraphM::display(int source,int target) const
{

#ifdef DEBUG
   cout << "in display" << endl;
#endif

   //size check
   if (size <= 0)
     return;



   //range check
   if ((source <= 0 || source > size) ||
      (target <= 0 && target > size ))
     return;

  cout << setw(4) << source << setw(5) << target;

  //if not path
  if (T[source][target].dist == INT_MAX)
  {
      cout << "       -----" << endl; 
  }
  else
  {
    cout << "       " << T[source][target].dist;
    cout << "  ";
    
    int *path = new int[size];
    for (int i = 0; i < size; i++)
      path[i] = 0;

    getPathHelper(source,target,path);
    //print path #s
    for(int i = 0; i < size; i++)
    {
        if (path[i] != 0) 
           cout << setw(3) << path[i];
    }
    cout << endl;
    //print path names
    for(int i = 0; i < size; i++)
    {
      if (path[i] != 0) 
        cout << *data[path[i]] << endl;
    }  

    //clean up
    delete []path;
  }  
      
}

//-----------------------------------------------------------------------------
// displayAll()
//     displays all graphs
//
//
void GraphM::displayAll() const
{
  cout << "Description               "
    << "From node  To Node  Dijkstra's  Path" 
    << endl;

  int *path = new int[size];
  for (int i = 0; i<size; i++)
    path[i] = 0;

  for (int i = 1; i <= size; i++)
  {
    cout << *data[i] << endl;
    for (int j = 1; j <= size; j++)
    {
      if (i == j) continue;

      cout << setw(30) << i; 
      cout << setw(10) << j; 
      if (T[i][j].dist == INT_MAX) 
      {
          cout << "      ----";
      }
      else
      {
        cout << setw(8) << T[i][j].dist << setw(10);
        getPathHelper(i,j,path);
        for (int p = 0 ; p < size; p++)
        {
          if (path[p] != 0)
            cout << " " << path[p];

          path[p] = 0;  //reset for next
        }
      } 
      cout << endl;
    
    }//end for j
    cout << endl;
  }//end for i
  delete []path;

   
 }


//-----------------------------------------------------------------------------
//  getPathHelper gets an array of the path
//
//
void GraphM::getPathHelper(int source,int target,int path[]) const
{
  int next=target;

#ifdef DEBUG
  cout << "\t\tin getPathHelper" << endl;
#endif
  
  for(int i = size-1; i >= 0; i--)
  {
     path[i] = next;

#ifdef DEBUG
          cout << "\t\t\tnext path = " << next << endl;
#endif

     if (next != 0)
        next = T[source][next].path; 

  }//end for

}//end getPathHelper

#pragma endregion display }}}




#pragma region debug {{{
//-----------------------------------------------------------------------------
//
// debug
//
void GraphM::debug()
{
   cout << "size" << size << endl;
   cout << " data = {" << endl;
   for(int i = 1; i <= size; i++)
   {
      if (data[i] != NULL)
        cout << "data[" << i << "] = " << *data[i] << endl;
   }
   cout << " } " << endl << endl;

   for(int i = 1; i <= size; i++)
   {
      for(int j = 1; j <= size; j++)
      {
         cout << "C[" << i << "][" << j << "] =" << C[i][j] << endl;
      }
   }

   cout << "T[][]" << endl;

   for(int i = 1; i <= size; i++)
   {
      cout << "        dist,path,visitied" << endl;
      for(int j = 1; j <= size; j++)
      {
         cout << "T[" << i << "][" << j << "] = " << T[i][j].dist << ":" << T[i][j].path << ":" << (T[i][j].visited ? "true" : "false")  << endl;
      }
   }
}

#pragma endregion debug }}}




